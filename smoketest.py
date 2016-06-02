#!/usr/bin/env python2.7


import pyxchange
import unittest
import io
import json


class Transport(object):
    def __init__(self):
        self.messages = []


    def write(self, data):
        for message in data.split('\n'):
            if message:
                self.messages.append(pyxchange.json_loads(message))


    def assertMessage(self, message):
        assert message in self.messages


    def loseConnection(self):
        pass


class JsonTest(unittest.TestCase):
    dct, sdct = { 'key': None }, '{"key": null}'

    def testLoads(self):
        """ Test JSON loads """

        assert pyxchange.json_loads('true')  is True
        assert pyxchange.json_loads('false') is False
        assert pyxchange.json_loads('null')  is None
        assert pyxchange.json_loads(self.sdct) == self.dct

        with self.assertRaises(TypeError):
            assert pyxchange.json_loads(None)


    def testDumps(self):
        """ Test JSON dumpss """

        assert pyxchange.json_dumps(True)  == 'true'
        assert pyxchange.json_dumps(False) == 'false'
        assert pyxchange.json_dumps(None)  == 'null'
        assert pyxchange.json_dumps(self.dct) == self.sdct

        with self.assertRaises(TypeError):
            assert pyxchange.json_dumps(object)


class MatcherTest(unittest.TestCase):
    createOrderRequest  = { u'orderId': 662688, u'price': 145,
                            u'message': u'createOrder', u'side': u'BUY', u'quantity': 350 }
    createOrderResponse = { u'report': u'NEW', u'orderId': 662688,
                            u'message': u'executionReport' }
    createOrderError = { u'report': u'ERROR', u'text': u'order already exists',
                         u'message': u'executionReport', u'orderId': 662688 }

    cancelOrderRequest  = { u'orderId': 662688, u'message': u'cancelOrder' }
    cancelOrderResponse = { u'orderId': 662688, u'message': u'executionReport', 'report': u'CANCELED' }
    cancelOrderError = { u'report': u'ERROR', u'text': u'order does not exists',
                         u'message': u'executionReport', u'orderId': 662688 }


    def setUp(self):
        self.transport = Transport()
        self.matcher = pyxchange.Matcher()
        self.trader = self.matcher.getTrader('trader-1', self.transport)

    def tearDown(self):
        self.matcher.removeTrader(self.trader)


    def testCreateCancelOrder(self):
        """ Test create/cancel order """

        self.matcher.handleMessageDict(self.trader, self.createOrderRequest)
        self.transport.assertMessage(self.createOrderResponse)

        self.matcher.handleMessageDict(self.trader, self.createOrderRequest)
        self.transport.assertMessage(self.createOrderError)

        self.matcher.handleMessageDict(self.trader, self.cancelOrderRequest)
        self.transport.assertMessage(self.cancelOrderResponse)

        self.matcher.handleMessageDict(self.trader, self.cancelOrderRequest)
        self.transport.assertMessage(self.cancelOrderError)


class TradingTest(unittest.TestCase):
    askOrders = [ { u'orderId': 1, u'price': 1000, u'message': u'createOrder',
                    u'side': u'SELL', u'quantity': 4 },
                  { u'orderId': 2, u'price': 1100, u'message': u'createOrder',
                    u'side': u'SELL', u'quantity': 3 },
                  { u'orderId': 3, u'price': 1200, u'message': u'createOrder',
                    u'side': u'SELL', u'quantity': 1 },
                  { u'orderId': 4, u'price': 1200, u'message': u'createOrder',
                    u'side': u'SELL', u'quantity': 8 },
                  { u'orderId': 5, u'price': 1300, u'message': u'createOrder',
                    u'side': u'SELL', u'quantity': 10 } ]

    def setUp(self):
        self.transport1 = Transport()
        self.transport2 = Transport()
        self.matcher = pyxchange.Matcher()
        self.trader1 = self.matcher.getTrader('trader-1', self.transport1)
        self.trader2 = self.matcher.getTrader('trader-2', self.transport2)


    def tearDown(self):
        self.matcher.removeTrader(self.trader1)
        self.matcher.removeTrader(self.trader2)


    def testBidMatchEvent(self):
        for createOrderRequest in self.askOrders:
            self.matcher.handleMessageDict(self.trader2, createOrderRequest)

        createOrderRequest  = { u'orderId': 1, u'price': 1200,
                                u'message': u'createOrder', u'side': u'BUY', u'quantity': 10 }

        self.matcher.handleMessageDict(self.trader1, createOrderRequest)


if __name__ == '__main__':
    unittest.main()


# EOF

