#!/usr/bin/env python3.5
#
# Simulate a simple market participant.
#
# Usage: client-participant.py PrivateChannelHostname PrivateChannelPort
#
# http://codingchallenge.wood.cz/



from typing import Any, Dict
import asyncio
import datetime
import json
import sys
import time
import utils



async def main():
	# Connect to the server
	assert len(sys.argv) == 3, 'Usage: client-participant.py PrivateChannelHostname PrivateChannelPort'
	host = sys.argv[1]
	port = int(sys.argv[2])
	reader, writer = await asyncio.open_connection(host, port)

	# Set up stdin
	userInput = asyncio.Queue()
	def onUserInput():
		userInput.put_nowait(sys.stdin.readline())
	loop = asyncio.get_event_loop()
	loop.add_reader(sys.stdin.fileno(), onUserInput)

	# Log incoming data
	bgLogger = asyncio.ensure_future(readIncomingData(reader))

	# Run Read-Eval-Print loop.
	try:
		await repl(userInput, writer)
	finally:
		bgLogger.cancel()
		writer.close()


async def readIncomingData(reader: asyncio.StreamReader) -> None:
	async for line in utils.LineReader(reader):
		print('\n<{!s} received {!r}>\n'.format(datetime.datetime.now(), line))


async def repl(userInput: asyncio.Queue, writer: asyncio.StreamWriter) -> None:
	while True:
		print('1: create order, 2: cancel order, q: quit')
		command = await prompt(userInput, 'Command?')

		if command == '1':
			side = await prompt(userInput, 'Side (BUY or SELL)?')
			assert side in {'BUY', 'SELL'}
			price = int(await prompt(userInput, 'Price?'))
			quantity = int(await prompt(userInput, 'Quantity?'))
			orderId = int(time.time() * 10) - 14617000000
			print('Assigning order ID', orderId)
			await sendMessage(writer, {
				'message': 'createOrder',
				'orderId': orderId,
				'side': side,
				'price': price,
				'quantity': quantity,
			})
		elif command == '2':
			orderId = await prompt(userInput, 'Order ID to cancel?')
			await sendMessage(writer, {
				'message': 'cancelOrder',
				'orderId': orderId,
			})
		elif command == 'q':
			break
		else:
			print('Unknown commad!')


async def prompt(userInput: asyncio.Queue, p: str) -> str:
	''' Prompt the user to enter a line and wait for their response. '''
	sys.stdout.write(p + ' ')
	sys.stdout.flush()
	line = await userInput.get()
	return line.rstrip('\n')


async def sendMessage(writer: asyncio.StreamWriter, msg: Dict[str, Any]) -> None:
	''' Encode and send a message to the server. '''
	data = json.dumps(msg)
	print('\n<{!s} sending {!r}>\n'.format(datetime.datetime.now(), data))
	writer.write(data.encode('utf-8') + b'\n')
	await writer.drain()



if __name__ == '__main__':
	loop = asyncio.get_event_loop()
	loop.run_until_complete(main())
