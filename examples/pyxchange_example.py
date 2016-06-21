#!/usr/bin/env python2.7
# -*- coding: utf-8 -*-

##
# @file pyxchange_example.py
# @brief Examples of using PyXchange
#
#

import logging

from pyxchange import engine, utils


class MessagePrinter(utils.BaseHandler):
    def __init__(self, name):
        super(MessagePrinter, self).__init__()

        self.name = name


    def handleMessage(self, message):
        """ On message callback """

        print self.name, '->', message


    def disconnect(self):
        """ On disconnect callback """

        pass


logging.basicConfig(level=logging.DEBUG)

matcher = engine.Matcher()
print matcher

name = 'client-1'
client1 = engine.Client(matcher, name, MessagePrinter(name))

name = 'trader-1'
trader1 = engine.Trader(matcher, name, MessagePrinter(name))

name = 'trader-2'
trader2 = engine.Trader(matcher, name, MessagePrinter(name))

print client1
print trader1
print trader2

trader1.ping()
trader2.ping()

print

# trader1 enters buy orders
trader1.createOrder({ 'orderId': 1, 'price': 10, 'quantity': 10, 'side': 'BUY' })
print

trader1.createOrder({ 'orderId': 2, 'price': 20, 'quantity': 10, 'side': 'BUY' })
print

trader1.createOrder({ 'orderId': 3, 'price': 30, 'quantity': 10, 'side': 'BUY' })
print

# this order will match with order 3 of trader1 and resting quantity will be inserted to orderbook
trader2.createOrder({ 'orderId': 1, 'price': 25, 'quantity': 15, 'side': 'SELL' })
print

# this could match with order 1 of trader2, but self-match prevention will reject it
trader2.createOrder({ 'orderId': 2, 'price': 25, 'quantity': 10, 'side': 'BUY' })
print

trader1.cancelOrder({ 'orderId': 2 })
print
# order does not exit
trader1.cancelOrder({ 'orderId': 2 })
print

trader2.cancelAll()
print


# EOF

