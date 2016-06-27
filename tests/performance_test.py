#!/usr/bin/env python2.7
# -*- coding: utf-8 -*-

##
# @file performance_test.py
# @brief Performance test of PyXchange
#
# Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
#
#

import json
import random
import optparse
import os

from twisted.internet import reactor, protocol
from twisted.protocols import basic as protocols
from twisted.internet.endpoints import TCP4ClientEndpoint


class TraderProtocol(protocols.LineOnlyReceiver):
    delimiter = '\n'

    def __init__(self, options):
        self.options = options
        self.orders = {}
        self.orderId = 0


    def connectionMade(self):
        for i in xrange(self.options.numOrders):
            self.createOrder()


    def lineReceived(self, message):
        message = json.loads(message)

        if self.options.print_messages:
            print message

        if message['message'] == 'executionReport':
            if message['report'] == 'NEW':
                self.handleNewOrder(message)
            elif message['report'] == 'FILL':
                self.handleFill(message)

            if message['orderId'] == self.orderId:
                reactor.stop()
                os._exit(0)


    def handleNewOrder(self, message):
        orderId  = message['orderId']
        quantity = message['quantity']

        if self.orders[orderId] != quantity:
            raise Exception('Quantity don\'t match')


    def handleFill(self, message):
        orderId = message['orderId']
        fillQty = message['quantity']

        self.orders[orderId] -= fillQty

        if self.orders[orderId] < 1:
            del(self.orders[orderId])


    def createOrder(self):
        def _createOrder(side, priceMin, priceMax):
            quantity = random.randint(1, 100)
            price = random.randint(priceMin, priceMax)

            self.orderId += 1
            self.orders[self.orderId] = quantity

            message = { 'orderId': self.orderId, 'price': price,
                        'quantity': quantity, 'message': 'createOrder', 'side': side }

            self.sendLine(json.dumps(message))

        sell = ( 'SELL', 1, 10 )
        buy  = ( 'BUY', 11, 20 )

        side, priceMin, priceMax = random.choice(( buy, sell ))

        _createOrder( side, priceMin, priceMax)


class TraderFactory(protocol.Factory):
    protocol = TraderProtocol

    def __init__(self, options):
        self.options = options


    def buildProtocol(self, addr):
        return self.protocol(self.options)


def parse_options():
    """ Parse command-line options """

    parser = optparse.OptionParser(
        usage = 'usage: %prog [options]',
        add_help_option = True
    )

    parser.add_option( '--host', '-H',
        action = 'store',
        dest = 'host',
        help = 'Matching engine - host',
        default = 'localhost'
    )

    parser.add_option( '--port', '-P',
        action = 'store',
        type = 'int',
        dest = 'port',
        help = 'Matching engine - port',
        default = 7000
    )

    parser.add_option( '--num', '-n',
        action = 'store',
        dest = 'numOrders',
        type = 'int',
        help = 'Number of orders',
        metavar = 'N',
        default = 100000
    )

    parser.add_option( '--print', '-p',
        action = 'store_true',
        dest = 'print_messages',
        help = 'Print messages',
        default = False
    )

    return parser.parse_args(args=None, values=None)


if __name__ == '__main__':
    options, args = parse_options()

    endpoint = TCP4ClientEndpoint(reactor, options.host, options.port)
    endpoint.connect(TraderFactory(options))

    reactor.run()


# EOF

