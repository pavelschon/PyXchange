#!/usr/bin/env python2.7


import pyxchange
import unittest
import io
import json


class Transport(object):
    def __init__(self):
        self.out = io.BytesIO()

    def write(self, data):
        self.out.write(data)


    def assertOutput(self, msg):
        assert self.out.getvalue().strip() == msg

        self.out.truncate(0)
        self.out.seek(0)


    def assertObj(self, obj):
        obj_ = json.loads(self.out.getvalue().strip())
        assert obj == obj_
        self.out.truncate(0)
        self.out.seek(0)


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


class ClientTest(unittest.TestCase):
    def setUp(self):
        self.transport = Transport()


    #def testWrite(self):
        #""" Test writing data into client's write function """

        #client, msg = pyxchange.Client('client', self.transport), 'data'

        #client.write(msg)

        #assert self.transport.assertOutput(msg)


    def testAddRemoveClient(self):
        """ Test add/remove client into matcher """

        matcher = pyxchange.Matcher()
        client = pyxchange.Client('client', self.transport)

        matcher.addClient(client)

        with self.assertRaises(ValueError):
            matcher.addClient(client)

        matcher.removeClient(client)

        with self.assertRaises(KeyError):
            matcher.removeClient(client)


class TraderTest(unittest.TestCase):
    def setUp(self):
        self.transport = Transport()


    def testWrite(self):
        """ Test writing data into trader's write function """

        trader, msg = pyxchange.Trader('trader', self.transport), 'data'

        trader.write(msg)

        self.transport.assertOutput(msg)


    def testAddTrader(self):
        """ Test add/remove trader into matcher """

        matcher = pyxchange.Matcher()
        trader = pyxchange.Trader('trader', self.transport)

        matcher.addTrader(trader)

        with self.assertRaises(ValueError):
            matcher.addTrader(trader)

        matcher.removeTrader(trader)

        with self.assertRaises(KeyError):
            matcher.removeTrader(trader)


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
        self.trader = pyxchange.Trader('trader', self.transport)
        self.matcher = pyxchange.Matcher()
        self.matcher.addTrader(self.trader)


    def testMalformedMessage(self):
        """ Test malformed message """

        message = 'malformed'

        with self.assertRaises(ValueError):
            self.matcher.handleMessageStr(self.trader, message)


    def testCreateCancelOrder(self):
        """ Test create/cancel order """

        self.matcher.handleMessageDict(self.trader, self.createOrderRequest)
        self.transport.assertObj(self.createOrderResponse)

        self.matcher.handleMessageDict(self.trader, self.createOrderRequest)
        self.transport.assertObj(self.createOrderError)

        self.matcher.handleMessageDict(self.trader, self.cancelOrderRequest)
        self.transport.assertObj(self.cancelOrderResponse)

        self.matcher.handleMessageDict(self.trader, self.cancelOrderRequest)
        self.transport.assertObj(self.cancelOrderError)


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
        self.trader1 = pyxchange.Trader('trader1', self.transport1)
        self.trader2 = pyxchange.Trader('trader2', self.transport2)
        self.matcher = pyxchange.Matcher()
        self.matcher.addTrader(self.trader1)
        self.matcher.addTrader(self.trader2)


    def testBidMatchEvent(self):
        for createOrderRequest in self.askOrders:
            self.matcher.handleMessageDict(self.trader2, createOrderRequest)

        createOrderRequest  = { u'orderId': 1, u'price': 1200,
                                u'message': u'createOrder', u'side': u'BUY', u'quantity': 10 }

        self.matcher.handleMessageDict(self.trader1, createOrderRequest)


if __name__ == '__main__':
    unittest.main()


# EOF

