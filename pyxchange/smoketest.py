#!/usr/bin/env python2.7

import unittest

import server
import engine

from test_utils import *


class JsonTest(unittest.TestCase):
    py, json = { 'key': None }, '{"key": null}'

    def testLoads(self):
        """ Test JSON loads """

        assert engine.json_loads('true')  is True
        assert engine.json_loads('false') is False
        assert engine.json_loads('null')  is None
        assert engine.json_loads(self.json) == self.py

        with self.assertRaises(TypeError):
            assert engine.json_loads(None)


    def testDumps(self):
        """ Test JSON dumps """

        assert engine.json_dumps(True)  == 'true'
        assert engine.json_dumps(False) == 'false'
        assert engine.json_dumps(None)  == 'null'
        assert engine.json_dumps(self.py) == self.json

        with self.assertRaises(TypeError):
            assert engine.json_dumps(object)


class MatcherTest(unittest.TestCase):
    def setUp(self):
        self.matcher = engine.Matcher()
        self.trader1 = TraderPair.create('trader-1', self.matcher)
        self.client1 = ClientPair.create('client-1', self.matcher)


    def tearDown(self):
        self.matcher.removeTrader(self.trader1.trader)
        self.matcher.removeClient(self.client1.client)


    def testCreateCancelOrder(self):
        """ Test create/cancel order """

        # create bid order
        self.matcher.handleMessageDict(self.trader1.trader, { u'orderId': 1, u'price': 1, u'quantity': 1, u'message': u'createOrder', u'side': u'BUY' })
        self.trader1.transport.assertMessage({ u'report': u'NEW', u'orderId': 1, u'quantity': 1, u'message': u'executionReport' })

        self.matcher.handleMessageDict(self.trader1.trader, { u'orderId': 2, u'price': 1, u'quantity': 1, u'message': u'createOrder', u'side': u'BUY' })
        self.trader1.transport.assertMessage({ u'report': u'NEW', u'orderId': 2, u'quantity': 1, u'message': u'executionReport' })

        self.client1.transport.assertMessage({ u'type': u'orderbook', u'side': u'bid', u'price': 1, 'quantity': 1})
        self.client1.transport.assertMessage({ u'type': u'orderbook', u'side': u'bid', u'price': 1, 'quantity': 2})

        # insert existing order
        self.matcher.handleMessageDict(self.trader1.trader, { u'orderId': 1, u'price': 1, u'quantity': 1, u'message': u'createOrder', u'side': u'BUY' })
        self.trader1.transport.assertMessage({u'text': u'order already exists', u'message': u'error'})

        # cancel order
        self.matcher.handleMessageDict(self.trader1.trader, { u'orderId': 1, u'message': u'cancelOrder' })
        self.trader1.transport.assertMessage({ u'orderId': 1, u'message': u'executionReport', 'report': u'CANCELED', u'quantity': 1 })

        self.client1.transport.assertMessage({ u'type': u'orderbook', u'side': u'bid', u'price': 1, 'quantity': 1})

        # cancel nonexistent order
        self.matcher.handleMessageDict(self.trader1.trader, { u'orderId': 1, u'message': u'cancelOrder' })
        self.trader1.transport.assertMessage({ u'text': u'order does not exists', u'message': u'error' })


if __name__ == '__main__':
    unittest.main()


# EOF

