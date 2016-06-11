#!/usr/bin/env python2.7

import unittest

from pyxchange import server
from pyxchange import engine

from pyxchange.utils import ClientWrapper, TraderWrapper


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
        """ Create matcher, one trader and one client (market data) """

        self.matcher = engine.Matcher()

        self.client1 = ClientWrapper('client-1', self.matcher)
        self.trader1 = TraderWrapper('trader-1', self.matcher)


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

        self.trader1.handleMessage({ u'message': u'test' })
        self.trader1.assertMessage({ u'text': u'unknown message', u'message': u'error' })


    def testPingPong(self):
        """ Test handling of ping/pong (heartbeat) messages """

        self.trader1.handleMessage({ u'message': u'ping' })
        self.trader1.assertMessage({ u'message': u'pong' })

        self.client1.handleMessage({ u'message': u'ping' })
        self.client1.assertMessage({ u'type': u'pong' })


    def testInvalidMessage(self):
        """ Test handling of bogus messages and invalid values """

        # wrong order id
        self.trader1.handleMessage({ u'orderId': 0, u'price': 1, u'quantity': 1, u'message': u'createOrder', u'side': u'BUY' })
        self.trader1.assertMessage({u'text': u'order has wrong order id', u'message': u'error'})

        # wrong type of order id (TypeError)
        self.trader1.handleMessage({ u'orderId': None, u'price': 1, u'quantity': 1, u'message': u'createOrder', u'side': u'BUY' })
        self.trader1.assertMessage({u'text': u'order has wrong order id', u'message': u'error'})

        # missing order id (KeyError)
        self.trader1.handleMessage({ u'price': 1, u'quantity': 1, u'message': u'createOrder', u'side': u'BUY' })
        self.trader1.assertMessage({u'text': u'order has wrong order id', u'message': u'error'})

        # wrong price
        self.trader1.handleMessage({ u'orderId': 1, u'price': 0, u'quantity': 1, u'message': u'createOrder', u'side': u'BUY' })
        self.trader1.assertMessage({u'text': u'order has wrong price', u'message': u'error'})

        # wront type of price (TypeError)
        self.trader1.handleMessage({ u'orderId': 1, u'price': None, u'quantity': 1, u'message': u'createOrder', u'side': u'BUY' })
        self.trader1.assertMessage({u'text': u'order has wrong price', u'message': u'error'})

        # missing price (KeyError)
        self.trader1.handleMessage({ u'orderId': 1, u'quantity': 1, u'message': u'createOrder', u'side': u'BUY' })
        self.trader1.assertMessage({u'text': u'order has wrong price', u'message': u'error'})

        # wrong quantity
        self.trader1.handleMessage({ u'orderId': 1, u'price': 1, u'quantity': 0, u'message': u'createOrder', u'side': u'BUY' })
        self.trader1.assertMessage({u'text': u'order has wrong quantity', u'message': u'error'})

        # wrong type of quantity (TypeError)
        self.trader1.handleMessage({ u'orderId': 1, u'price': 1, u'quantity': None, u'message': u'createOrder', u'side': u'BUY' })
        self.trader1.assertMessage({u'text': u'order has wrong quantity', u'message': u'error'})

        # missing quantity (KeyError)
        self.trader1.handleMessage({ u'orderId': 1, u'price': 1, u'message': u'createOrder', u'side': u'BUY' })
        self.trader1.assertMessage({u'text': u'order has wrong quantity', u'message': u'error'})

        # wrong type of side (TypeError)
        self.trader1.handleMessage({ u'orderId': 1, u'price': 1, u'quantity': 1, u'message': u'createOrder', u'side': None })
        self.trader1.assertMessage({u'text': u'order has wrong side', u'message': u'error'})

        # missing side (KeyError)
        self.trader1.handleMessage({ u'orderId': 1, u'price': 1, u'quantity': 1, u'message': u'createOrder' })
        self.trader1.assertMessage({u'text': u'order has wrong side', u'message': u'error'})

        # wrong order id
        self.trader1.handleMessage({ u'orderId': 0, u'message': u'cancelOrder' })
        self.trader1.assertMessage({u'text': u'order has wrong order id', u'message': u'error'})

        # wrong type of order id (TypeError)
        self.trader1.handleMessage({ u'orderId': None, u'message': u'cancelOrder' })
        self.trader1.assertMessage({u'text': u'order has wrong order id', u'message': u'error'})

        # missing order id (KeyError)
        self.trader1.handleMessage({ u'message': u'cancelOrder' })
        self.trader1.assertMessage({u'text': u'order has wrong order id', u'message': u'error'})


    def testCreateCancelOrder(self):
        """ Test create/cancel order """

        # create bid order
        self.trader1.handleMessage({ u'orderId': 1, u'price': 1, u'quantity': 1, u'message': u'createOrder', u'side': u'BUY' })
        self.trader1.assertMessage({ u'report': u'NEW', u'orderId': 1, u'quantity': 1, u'message': u'executionReport' })

        self.trader1.handleMessage({ u'orderId': 2, u'price': 1, u'quantity': 1, u'message': u'createOrder', u'side': u'BUY' })
        self.trader1.assertMessage({ u'report': u'NEW', u'orderId': 2, u'quantity': 1, u'message': u'executionReport' })

        self.client1.assertMessage({ u'type': u'orderbook', u'side': u'bid', u'price': 1, 'quantity': 1})
        self.client1.assertMessage({ u'type': u'orderbook', u'side': u'bid', u'price': 1, 'quantity': 2})

        # insert existing order
        self.trader1.handleMessage({ u'orderId': 1, u'price': 1, u'quantity': 1, u'message': u'createOrder', u'side': u'BUY' })
        self.trader1.assertMessage({u'text': u'order already exists', u'message': u'error'})

        # cancel order
        self.trader1.handleMessage({ u'orderId': 1, u'message': u'cancelOrder' })
        self.trader1.assertMessage({ u'orderId': 1, u'message': u'executionReport', 'report': u'CANCELED', u'quantity': 1 })
        self.client1.assertMessage({ u'type': u'orderbook', u'side': u'bid', u'price': 1, 'quantity': 1})

        # cancel nonexistent order
        self.trader1.handleMessage({ u'orderId': 1, u'message': u'cancelOrder' })
        self.trader1.assertMessage({ u'text': u'order does not exists', u'message': u'error' })

        # test orders are removed when trader disconnects
        self.trader1.handleMessage({ u'message': u'cancelAll' })

        self.client1.assertMessage({u'price': 1, u'type': u'orderbook', u'side': u'bid', u'quantity': 0})


class TradingTest(unittest.TestCase):
    def setUp(self):
        self.matcher = engine.Matcher()

        self.client1 = ClientWrapper('client-1', self.matcher)
        self.trader1 = TraderWrapper('trader-1', self.matcher)
        self.trader2 = TraderWrapper('trader-2', self.matcher)

        # enter some bid orders
        self.trader1.handleMessage({ u'orderId': 1, u'price': 10, u'quantity': 10, u'message': u'createOrder', u'side': u'BUY' })
        self.trader1.handleMessage({ u'orderId': 2, u'price': 20, u'quantity': 10, u'message': u'createOrder', u'side': u'BUY' })
        self.trader1.handleMessage({ u'orderId': 3, u'price': 30, u'quantity': 10, u'message': u'createOrder', u'side': u'BUY' })

        # enter some ask orders
        self.trader2.handleMessage({ u'orderId': 1, u'price': 40, u'quantity': 10, u'message': u'createOrder', u'side': u'SELL' })
        self.trader2.handleMessage({ u'orderId': 2, u'price': 50, u'quantity': 10, u'message': u'createOrder', u'side': u'SELL' })
        self.trader2.handleMessage({ u'orderId': 3, u'price': 60, u'quantity': 10, u'message': u'createOrder', u'side': u'SELL' })

        # clear messages received until now
        self.client1.clear()
        self.trader1.clear()
        self.trader2.clear()


    def tearDown(self):
        self.client1.remove()
        self.trader1.remove()
        self.trader2.remove()


    def testTrade(self):
        self.trader2.handleMessage({ u'orderId': 4, u'price': 15, u'quantity': 25, u'message': u'createOrder', u'side': u'SELL' })

        self.trader1.assertMessage({u'report': u'FILL', u'orderId': 3, u'message': u'executionReport', u'price': 30, u'quantity': 10})
        self.trader2.assertMessage({u'report': u'FILL', u'orderId': 4, u'message': u'executionReport', u'price': 30, u'quantity': 10})
        self.client1.assertMessage({u'price': 30, u'time': 0, u'type': u'trade', u'quantity': 10})

        self.trader1.assertMessage({u'report': u'FILL', u'orderId': 2, u'message': u'executionReport', u'price': 20, u'quantity': 10})
        self.trader2.assertMessage({u'report': u'FILL', u'orderId': 4, u'message': u'executionReport', u'price': 20, u'quantity': 10})
        self.client1.assertMessage({u'price': 20, u'time': 0, u'type': u'trade', u'quantity': 10})

        # remaining quantity of order 4 is inserted to orderbook
        self.trader2.assertMessage({u'report': u'NEW', u'orderId': 4, u'message': u'executionReport', u'quantity': 5})

        self.client1.assertMessage({u'price': 30, u'type': u'orderbook', u'side': u'bid', u'quantity': 0})
        self.client1.assertMessage({u'price': 20, u'type': u'orderbook', u'side': u'bid', u'quantity': 0})
        self.client1.assertMessage({u'price': 15, u'type': u'orderbook', u'side': u'ask', u'quantity': 5})


    def testSelfMatch(self):
        # self-match protection
        self.trader2.handleMessage({ u'orderId': 4, u'price': 40, u'quantity': 10, u'message': u'createOrder', u'side': u'BUY' })
        self.trader2.assertMessage({u'text': u'self-match rejected', u'message': u'error'})


if __name__ == '__main__':
    unittest.main()


# EOF

