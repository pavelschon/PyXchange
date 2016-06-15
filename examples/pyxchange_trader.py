#!/usr/bin/env python2.7
# -*- coding: utf-8 -*-

import json
import random
import time

from twisted.internet import reactor, protocol
from twisted.protocols import basic as protocols
from twisted.internet.endpoints import TCP4ClientEndpoint


class TraderProtocol(protocols.LineOnlyReceiver):
    delimiter = '\n'

    def __init__(self):
        self.orders = {}
        self.orderId = 0

    def connectionMade(self):
        for i in xrange(10000):
            self.createOrder()

    def lineReceived(self, message):
        message = json.loads(message)

        if message['message'] == 'executionReport':
            if message['report'] == 'NEW':
                self.handleNewOrder(message)


    def handleNewOrder(self, message):
        orderId = message['orderId']
        if self.orders[orderId] != message['quantity']:
            raise Exception('Quantity don\'t match')


    def createOrder(self):
        price = random.randint(10, 20)
        quantity = random.randint(1, 10)
        self.orderId += 1
        self.orders[self.orderId] = quantity

        message = { 'orderId': self.orderId, 'price': price,
                    'quantity': quantity, 'message': 'createOrder', 'side': 'BUY' }

        self.sendLine(json.dumps(message))



class TraderFactory(protocol.Factory):
    protocol = TraderProtocol


point = TCP4ClientEndpoint(reactor, 'localhost', 7000)
d = point.connect(TraderFactory())
reactor.run()


# EOF

