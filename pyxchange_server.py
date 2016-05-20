#!/usr/bin/env python2.7

from twisted.internet import reactor, protocol

import pyxchange


class ClientProtocol(protocol.Protocol):
    """ Market-data client protocol """

    def __init__(self, factory, addr):
        self.factory = factory


    def dataReceived(self, data):
        self.client.write(repr(matcher) + ' ' + repr(self.client) + '\n')


    def connectionMade(self):
        self.client = pyxchange.Client(self.transport.write)

        self.factory.matcher.addClient(self.client)


    def connectionLost(self, reason):
        self.factory.matcher.removeClient(self.client)


class ClientFactory(protocol.Factory):
    """ Factory for market-data client protocol """

    def __init__(self, matcher):
        self.matcher = matcher


    def buildProtocol(self, addr):
        return ClientProtocol(self, addr)


class TraderProtocol(protocol.Protocol):
    """ Trader protocol of market participants """

    def __init__(self, factory, addr):
        self.factory = factory


    def connectionMade(self):
        self.trader = pyxchange.Trader(self.transport.write)

        self.factory.matcher.addTrader(self.trader)


    def dataReceived(self, data):
        self.trader.write(repr(matcher) + ' ' + repr(self.trader) + '\n')


    def connectionLost(self, reason):
        self.factory.matcher.removeTrader(self.trader)


class TraderFactory(protocol.Factory):
    """ Factory for Trader protocol """

    def __init__(self, matcher):
        self.matcher = matcher


    def buildProtocol(self, addr):
        return TraderProtocol(self, addr)



if __name__ == '__main__':
    matcher = pyxchange.Matcher()

    reactor.listenTCP(7001, TraderFactory(matcher)) # market participants
    reactor.listenTCP(7002, ClientFactory(matcher)) # market-data clients

    reactor.run()


# EOF

