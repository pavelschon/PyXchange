#!/usr/bin/env python2.7
# -*- coding: utf-8 -*-

##
# @file unit_test.py
# @brief Unittest of PyXchange
#
#

import logging
import unittest
import pyxchange


class JsonTest(unittest.TestCase):
    py, json = { 'key': None }, '{"key": null}'

    def testLoads(self):
        """ Test JSON loads """

        assert pyxchange.json_loads('true')  is True
        assert pyxchange.json_loads('false') is False
        assert pyxchange.json_loads('null')  is None
        assert pyxchange.json_loads(self.json) == self.py

        with self.assertRaises(TypeError):
            assert pyxchange.json_loads(None)


    def testDumps(self):
        """ Test JSON dumps """

        assert pyxchange.json_dumps(True)  == 'true'
        assert pyxchange.json_dumps(False) == 'false'
        assert pyxchange.json_dumps(None)  == 'null'
        assert pyxchange.json_dumps(self.py) == self.json

        with self.assertRaises(TypeError):
            assert pyxchange.json_dumps(object)


class MatcherTest(unittest.TestCase):
    def setUp(self):
        """ Create matcher, one trader and one client (market data) """

        self.matcher = pyxchange.Matcher()

        self.client1 = pyxchange.ClientWrapper('client-1', self.matcher)
        self.trader1 = pyxchange.TraderWrapper('trader-1', self.matcher)


    def tearDown(self):
        """ Remove client and trader from the matcher """
        self.client1.remove()
        self.trader1.remove()


    def testWrongTransport(self):
        """ Test wrong transport object """

        with self.assertRaises(AttributeError):
            self.matcher.getTrader('trader-2', None)


    def testTypeError(self):
        """ Test handling of non-dict data """

        self.trader1.handleMessage('null')
        self.trader1.assertDisconnected()


    def testUnknownMessage(self):
        """ Test handling of unknown message """

        self.trader1.handleMessage({ 'message': 'test' })
        self.trader1.assertMessage({ 'text': 'unknown message', 'message': 'error' })


    def testPingPong(self):
        """ Test handling of ping/pong (heartbeat) messages """

        self.trader1.handleMessage({ 'message': 'ping' })
        self.trader1.assertMessage({ 'message': 'pong' })


    def testInvalidMessage(self):
        """ Test handling of bogus messages and invalid values """

        # wrong order id
        self.trader1.handleMessage({ 'orderId': 0, 'price': 1, 'quantity': 1, 'message': 'createOrder', 'side': 'BUY' })
        self.trader1.assertMessage({'text': 'order has wrong order id', 'message': 'error'})

        # wrong type of order id (TypeError)
        self.trader1.handleMessage({ 'orderId': None, 'price': 1, 'quantity': 1, 'message': 'createOrder', 'side': 'BUY' })
        self.trader1.assertMessage({ 'text': 'order has wrong order id', 'message': 'error' })

        # missing order id (KeyError)
        self.trader1.handleMessage({ 'price': 1, 'quantity': 1, 'message': 'createOrder', 'side': 'BUY' })
        self.trader1.assertMessage({ 'text': 'order has wrong order id', 'message': 'error' })

        # wrong price
        self.trader1.handleMessage({ 'orderId': 1, 'price': 0, 'quantity': 1, 'message': 'createOrder', 'side': 'BUY' })
        self.trader1.assertMessage({ 'text': 'order has wrong price', 'message': 'error' })

        # wront type of price (TypeError)
        self.trader1.handleMessage({ 'orderId': 1, 'price': None, 'quantity': 1, 'message': 'createOrder', 'side': 'BUY' })
        self.trader1.assertMessage({ 'text': 'order has wrong price', 'message': 'error' })

        # missing price (KeyError)
        self.trader1.handleMessage({ 'orderId': 1, 'quantity': 1, 'message': 'createOrder', 'side': 'BUY' })
        self.trader1.assertMessage({ 'text': 'order has wrong price', 'message': 'error' })

        # wrong quantity
        self.trader1.handleMessage({ 'orderId': 1, 'price': 1, 'quantity': 0, 'message': 'createOrder', 'side': 'BUY' })
        self.trader1.assertMessage({ 'text': 'order has wrong quantity', 'message': 'error' })

        # wrong type of quantity (TypeError)
        self.trader1.handleMessage({ 'orderId': 1, 'price': 1, 'quantity': None, 'message': 'createOrder', 'side': 'BUY' })
        self.trader1.assertMessage({ 'text': 'order has wrong quantity', 'message': 'error' })

        # missing quantity (KeyError)
        self.trader1.handleMessage({ 'orderId': 1, 'price': 1, 'message': 'createOrder', 'side': 'BUY' })
        self.trader1.assertMessage({ 'text': 'order has wrong quantity', 'message': 'error' })

        # wrong type of side (TypeError)
        self.trader1.handleMessage({ 'orderId': 1, 'price': 1, 'quantity': 1, 'message': 'createOrder', 'side': None })
        self.trader1.assertMessage({ 'text': 'order has wrong side', 'message': 'error' })

        # missing side (KeyError)
        self.trader1.handleMessage({ 'orderId': 1, 'price': 1, 'quantity': 1, 'message': 'createOrder' })
        self.trader1.assertMessage({ 'text': 'order has wrong side', 'message': 'error' })

        # wrong order id
        self.trader1.handleMessage({ 'orderId': 0, 'message': 'cancelOrder' })
        self.trader1.assertMessage({ 'text': 'order has wrong order id', 'message': 'error' })

        # wrong type of order id (TypeError)
        self.trader1.handleMessage({ 'orderId': None, 'message': 'cancelOrder' })
        self.trader1.assertMessage({ 'text': 'order has wrong order id', 'message': 'error' })

        # missing order id (KeyError)
        self.trader1.handleMessage({ 'message': 'cancelOrder' })
        self.trader1.assertMessage({ 'text': 'order has wrong order id', 'message': 'error' })


    def testCreateCancelOrder(self):
        """ Test create/cancel order """

        # create bid order
        self.trader1.handleMessage({ 'orderId': 1, 'price': 1, 'quantity': 1, 'message': 'createOrder', 'side': 'BUY' })
        self.trader1.assertMessage({ 'report': 'NEW', 'orderId': 1, 'quantity': 1, 'message': 'executionReport' })

        self.trader1.handleMessage({ 'orderId': 2, 'price': 1, 'quantity': 1, 'message': 'createOrder', 'side': 'BUY' })
        self.trader1.assertMessage({ 'report': 'NEW', 'orderId': 2, 'quantity': 1, 'message': 'executionReport' })

        self.client1.assertMessage({ 'type': 'orderbook', 'side': 'bid', 'price': 1, 'quantity': 1})
        self.client1.assertMessage({ 'type': 'orderbook', 'side': 'bid', 'price': 1, 'quantity': 2})

        # insert existing order
        self.trader1.handleMessage({ 'orderId': 1, 'price': 1, 'quantity': 1, 'message': 'createOrder', 'side': 'BUY' })
        self.trader1.assertMessage({ 'text': 'order already exists', 'message': 'error' })

        # cancel order
        self.trader1.handleMessage({ 'orderId': 1, 'message': 'cancelOrder' })
        self.trader1.assertMessage({ 'orderId': 1, 'message': 'executionReport', 'report': 'CANCELED', 'quantity': 1 })
        self.client1.assertMessage({ 'type': 'orderbook', 'side': 'bid', 'price': 1, 'quantity': 1})

        # cancel nonexistent order
        self.trader1.handleMessage({ 'orderId': 1, 'message': 'cancelOrder' })
        self.trader1.assertMessage({ 'text': 'order does not exists', 'message': 'error' })

        # test orders are removed when trader disconnects
        self.trader1.handleMessage({ 'message': 'cancelAll' })

        self.client1.assertMessage({'price': 1, 'type': 'orderbook', 'side': 'bid', 'quantity': 0})


class TradingTest(unittest.TestCase):
    def setUp(self):
        self.matcher = pyxchange.Matcher()

        self.client1 = pyxchange.ClientWrapper('client-1', self.matcher)
        self.trader1 = pyxchange.TraderWrapper('trader-1', self.matcher)
        self.trader2 = pyxchange.TraderWrapper('trader-2', self.matcher)

        # enter some bid orders
        self.trader1.handleMessage({ 'orderId': 1, 'price': 10, 'quantity': 10, 'message': 'createOrder', 'side': 'BUY' })
        self.trader1.handleMessage({ 'orderId': 2, 'price': 20, 'quantity': 10, 'message': 'createOrder', 'side': 'BUY' })
        self.trader1.handleMessage({ 'orderId': 3, 'price': 30, 'quantity': 10, 'message': 'createOrder', 'side': 'BUY' })

        # enter some ask orders
        self.trader2.handleMessage({ 'orderId': 1, 'price': 40, 'quantity': 10, 'message': 'createOrder', 'side': 'SELL' })
        self.trader2.handleMessage({ 'orderId': 2, 'price': 50, 'quantity': 10, 'message': 'createOrder', 'side': 'SELL' })
        self.trader2.handleMessage({ 'orderId': 3, 'price': 60, 'quantity': 10, 'message': 'createOrder', 'side': 'SELL' })

        # clear messages received until now
        self.client1.clear()
        self.trader1.clear()
        self.trader2.clear()


    def tearDown(self):
        self.client1.remove()
        self.trader1.remove()
        self.trader2.remove()


    def testTrade(self):
        self.trader2.handleMessage({ 'orderId': 4, 'price': 15, 'quantity': 25, 'message': 'createOrder', 'side': 'SELL' })

        self.trader1.assertMessage({ 'report': 'FILL', 'orderId': 3, 'message': 'executionReport', 'price': 30, 'quantity': 10 })
        self.trader1.assertMessage({ 'report': 'FILL', 'orderId': 2, 'message': 'executionReport', 'price': 20, 'quantity': 10 })

        self.trader2.assertMessage({ 'report': 'FILL', 'orderId': 4, 'message': 'executionReport', 'price': 30, 'quantity': 10 })
        self.trader2.assertMessage({ 'report': 'FILL', 'orderId': 4, 'message': 'executionReport', 'price': 20, 'quantity': 10 })

        # remaining quantity of order 4 is inserted to orderbook
        self.trader2.assertMessage({ 'report': 'NEW', 'orderId': 4, 'message': 'executionReport', 'quantity': 5 })

        self.client1.assertMessage({ 'price': 30, 'time': 0, 'type': 'trade', 'quantity': 10 })
        self.client1.assertMessage({ 'price': 20, 'time': 0, 'type': 'trade', 'quantity': 10 })
        self.client1.assertMessage({ 'price': 30, 'type': 'orderbook', 'side': 'bid', 'quantity': 0 })
        self.client1.assertMessage({ 'price': 20, 'type': 'orderbook', 'side': 'bid', 'quantity': 0 })
        self.client1.assertMessage({ 'price': 15, 'type': 'orderbook', 'side': 'ask', 'quantity': 5 })


    def testMarketSellOrder(self):
        self.trader2.handleMessage({ 'quantity': 25, 'message': 'marketOrder', 'side': 'SELL' })

        self.trader1.assertMessage({ 'report': 'FILL', 'orderId': 3, 'message': 'executionReport', 'price': 30, 'quantity': 10 })
        self.trader1.assertMessage({ 'report': 'FILL', 'orderId': 2, 'message': 'executionReport', 'price': 20, 'quantity': 10 })

        self.trader2.assertMessage({ 'report': 'FILL', 'orderId': 0, 'message': 'executionReport', 'price': 30, 'quantity': 10 })
        self.trader2.assertMessage({ 'report': 'FILL', 'orderId': 0, 'message': 'executionReport', 'price': 20, 'quantity': 10 })

        self.client1.assertMessage({ 'price': 30, 'time': 0, 'type': 'trade', 'quantity': 10 })
        self.client1.assertMessage({ 'price': 20, 'time': 0, 'type': 'trade', 'quantity': 10 })
        self.client1.assertMessage({ 'price': 10, 'time': 0, 'type': 'trade', 'quantity': 5 })

        self.client1.assertMessage({ 'price': 30, 'type': 'orderbook', 'side': 'bid', 'quantity': 0 })
        self.client1.assertMessage({ 'price': 20, 'type': 'orderbook', 'side': 'bid', 'quantity': 0 })
        self.client1.assertMessage({ 'price': 10, 'type': 'orderbook', 'side': 'bid', 'quantity': 5 })


    def testMarketBuyOrder(self):
        self.trader1.handleMessage({ 'quantity': 25, 'message': 'marketOrder', 'side': 'BUY' })

        self.trader2.assertMessage({ 'report': 'FILL', 'orderId': 1, 'message': 'executionReport', 'price': 40, 'quantity': 10 })
        self.trader2.assertMessage({ 'report': 'FILL', 'orderId': 2, 'message': 'executionReport', 'price': 50, 'quantity': 10 })

        self.client1.assertMessage({ 'price': 40, 'time': 0, 'type': 'trade', 'quantity': 10 })
        self.client1.assertMessage({ 'price': 50, 'time': 0, 'type': 'trade', 'quantity': 10 })
        self.client1.assertMessage({ 'price': 60, 'time': 0, 'type': 'trade', 'quantity': 5 })

        self.client1.assertMessage({ 'price': 40, 'type': 'orderbook', 'side': 'ask', 'quantity': 0 })
        self.client1.assertMessage({ 'price': 50, 'type': 'orderbook', 'side': 'ask', 'quantity': 0 })
        self.client1.assertMessage({ 'price': 60, 'type': 'orderbook', 'side': 'ask', 'quantity': 5 })


if __name__ == '__main__':
    logging.basicConfig(level=logging.CRITICAL)

    unittest.main()


# EOF

