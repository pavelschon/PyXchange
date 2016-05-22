#!/usr/bin/env python2.7


import pyxchange
import unittest
import io
import json


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
        self.transport = io.BytesIO()


    def testWrite(self):
        """ Test writing data into client's write function """

        client, msg = pyxchange.Client(self.transport.write), 'data'

        client.write(msg)

        assert self.transport.getvalue() == 'data'


    def testBadWrite(self):
        """ Test whether client throws error on bad write """

        client, msg = pyxchange.Client(None), 'data'

        with self.assertRaises(TypeError):
            client.write(msg)


    def testAddRemoveClient(self):
        """ Test add/remove client into matcher """

        matcher = pyxchange.Matcher()
        client = pyxchange.Client(self.transport.write)

        matcher.addClient(client)

        with self.assertRaises(ValueError):
            matcher.addClient(client)

        matcher.removeClient(client)

        with self.assertRaises(KeyError):
            matcher.removeClient(client)


class TraderTest(unittest.TestCase):
    def setUp(self):
        self.transport = io.BytesIO()


    def testWrite(self):
        """ Test writing data into trader's write function """

        trader, msg = pyxchange.Trader(self.transport.write), 'data'

        trader.write(msg)

        assert self.transport.getvalue() == msg


    def testBadWrite(self):
        """ Test whether client throws error on bad write """

        trader, msg = pyxchange.Trader(None), 'data'

        with self.assertRaises(TypeError):
            trader.write(msg)


    def testAddTrader(self):
        """ Test add/remove trader into matcher """

        matcher = pyxchange.Matcher()
        trader = pyxchange.Trader(self.transport.write)

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

    cancelOrderRequest  = { u'orderId': 662688, u'message': u'cancelOrder' }
    cancelOrderResponse = { u'orderId': 662688, u'message': u'executionReport', 'report': u'CANCELED' }


    def setUp(self):
        self.transport = io.BytesIO()
        self.trader = pyxchange.Trader(self.transport.write)
        self.matcher = pyxchange.Matcher()
        self.matcher.addTrader(self.trader)


    def testMalformedMessage(self):
        """ Test malformed message """

        message = 'malformed'

        with self.assertRaises(ValueError):
            self.matcher.handleMessageStr(self.trader, message)


    def testCreateOrder(self):
        """ Test create/cancel order """

        self.matcher.handleMessageDict(self.trader, self.createOrderRequest)

        assert pyxchange.json_loads(self.transport.getvalue()) == self.createOrderResponse

        self.transport.seek(0)

        with self.assertRaises(ValueError):
            self.matcher.handleMessageDict(self.trader, self.createOrderRequest)

        self.transport.seek(0)

        self.matcher.handleMessageDict(self.trader, self.cancelOrderRequest)

        assert pyxchange.json_loads(self.transport.getvalue()) == self.cancelOrderResponse
        self.transport.seek(0)

        with self.assertRaises(ValueError):
            self.matcher.handleMessageDict(self.trader, self.cancelOrderRequest)




if __name__ == '__main__':
    unittest.main()


# EOF

