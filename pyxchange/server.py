#!/usr/bin/env python2.7
##
# @file server.py
# @brief FIXME
#
#

import logging

from twisted.internet import protocol


class ClientProtocol(protocol.Protocol):
    """ Market-data client protocol """

    def __init__(self, factory, addr):
        self.factory = factory
        self.matcher = factory.matcher
        self.name = '%s:%s' % ( addr.host, addr.port )
        self.logger = logging.getLogger()


    def connectionMade(self):
        self.client = self.matcher.getClient(self.name, self.transport)


    def connectionLost(self, reason):
        self.matcher.removeClient(self.client)


class TraderProtocol(protocol.Protocol):
    """ Trader protocol of market participants """

    def __init__(self, factory, addr):
        self.factory = factory
        self.matcher = factory.matcher
        self.name = '%s:%s' % ( addr.host, addr.port )
        self.logger = logging.getLogger()


    def connectionMade(self):
        self.trader = self.matcher.getTrader(self.name, self.transport)


    def connectionLost(self, reason):
        self.matcher.removeTrader(self.trader)


    def dataReceived(self, data):
        data = data.strip()
        if data:
            try:
                self.trader.handleMessageStr(self.matcher, data)
            except Exception:
                self.onException()


    def onException(self):
        self.logger.exception('%s caused error on trading interface' % self.trader)

        self.transport.loseConnection()


class ClientFactory(protocol.Factory):
    """ Factory for market-data client protocol """

    def __init__(self, matcher):
        self.matcher = matcher


    def buildProtocol(self, addr):
        return ClientProtocol(self, addr)


class TraderFactory(protocol.Factory):
    """ Factory for Trader protocol """

    def __init__(self, matcher):
        self.matcher = matcher


    def buildProtocol(self, addr):
        return TraderProtocol(self, addr)


# EOF

