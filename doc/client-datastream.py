#!/usr/bin/env python3.5
#
# Simulate a data stream consumer.
#
# Usage: client-datastream.py DataChannelHostname DataChannelPort
#
# http://codingchallenge.wood.cz/



from typing import Any, Dict
import asyncio
import datetime
import json
import sys
import utils



async def main():
	# Connect to the server
	assert len(sys.argv) == 3, 'Usage: client-datastream.py DataChannelHostname DataChannelPort'
	host = sys.argv[1]
	port = int(sys.argv[2])
	reader, writer = await asyncio.open_connection(host, port)

	# Receive and parse incoming data
	model = MarketModel()
	try:
		async for line in utils.LineReader(reader):
			print('\n<{!s} received {!r}>\n'.format(datetime.datetime.now(), line))
			model.apply(json.loads(line))
			print(model)
	finally:
		writer.close()


class MarketModel:
	''' Represent the current state of the market (order book, trades). '''

	def __init__(self) -> None:
		self._trades = [] # type: List[Dict[str, Any]]
		self._bid = {} # type: Dict[int, int]
		self._ask = {} # type: Dict[int, int]


	def apply(self, message: Dict[str, Any]) -> None:
		if message['type'] == 'trade':
			self._trades.append({
				'time': datetime.datetime.fromtimestamp(message['time']),
				'price': message['price'],
				'quantity': message['quantity'],
			})
		elif message['type'] == 'orderbook':
			assert message['side'] in {'bid', 'ask'}, 'Invalid order book side'
			side = self._bid if message['side'] == 'bid' else self._ask
			side[message['price']] = message['quantity']
		else:
			raise ValueError('Invalid message type')


	def __repr__(self) -> str:
		lines = (
			['BID'] + [ '{:d} @ {:d}'.format(qty, price) for (price, qty) in reversed(sorted(self._bid.items())) if qty ] +
			['ASK'] + [ '{:d} @ {:d}'.format(qty, price) for (price, qty) in sorted(self._ask.items()) if qty ] +
			['TRADES'] + [ '{time:%Y-%m-%d %H:%M:%S.%s} - {quantity:d} @ {price:d}'.format(**trade) for trade in self._trades ]
		)
		return '\n'.join(lines)



if __name__ == '__main__':
	loop = asyncio.get_event_loop()
	loop.run_until_complete(main())
