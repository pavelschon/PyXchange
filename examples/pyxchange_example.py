#!/usr/bin/env python
##
# @file pyxchange_example.py
# @brief FIXME
#
#

from pyxchange import engine, Transport


class MessagePrinter(Transport):
    def __init__(self, name):
        super(MessagePrinter, self).__init__()

        self.name = name


    def writeData(self, message):
        """ On message callback """

        super(MessagePrinter, self).writeData(message)

        print self.name, '->', message


# you can pass logging.Logger instance to Matcher
#matcher = engine.Matcher(logger)
matcher = engine.Matcher()
print matcher

# uncomment this to get public market data messages
#client1_transport = MessagePrinter('client-1')
#client1 = matcher.getClient('client-1', client1_transport)
#print client1

trader1_transport = MessagePrinter('trader-1')
trader1 = matcher.getTrader('trader-1', trader1_transport)
print trader1

trader2_transport = MessagePrinter('trader-2')
trader2 = matcher.getTrader('trader-2', trader2_transport)
print trader2

# trader1 enters buy orders
trader1.createOrder(matcher, { 'orderId': 1, 'price': 10, 'quantity': 10, 'side': 'BUY' })
trader1.createOrder(matcher, { 'orderId': 2, 'price': 20, 'quantity': 10, 'side': 'BUY' })
trader1.createOrder(matcher, { 'orderId': 3, 'price': 30, 'quantity': 10, 'side': 'BUY' })

# this order will match with order 3 of trader1 and resting quantity will be inserted to orderbook
trader2.createOrder(matcher, { 'orderId': 1, 'price': 25, 'quantity': 15, 'side': 'SELL' })


# this could match with order 1 of trader2, but self-match prevention will reject it
trader2.createOrder(matcher, { 'orderId': 2, 'price': 25, 'quantity': 10, 'side': 'BUY' })

trader1.cancelOrder(matcher, { 'orderId': 2 })
# order does not exit
trader1.cancelOrder(matcher, { 'orderId': 2 })

matcher.removeTrader(trader1) # this will cancel all orders of trader1
matcher.removeTrader(trader2) # this will cancel all orders of trader2



# EOF

