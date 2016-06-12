#!/usr/bin/env python2.7
##
# @file server.py
# @brief FIXME
#
#

import logging

from twisted.internet import protocol

from . import engine


class ClientProtocol(protocol.Protocol):
    """ Market-data client protocol """

    def __init__(self, factory, addr):
        self.factory = factory
        self.matcher = factory.matcher
        self.name = '%s:%s' % ( addr.host, addr.port )
        self.logger = logging.getLogger()


    def connectionMade(self):
        self.client = engine.Client(self.matcher, self.name, self.transport)


class TraderProtocol(protocol.Protocol):
    """ Trader protocol of market participants """

    def __init__(self, factory, addr):
        self.factory = factory
        self.matcher = factory.matcher
        self.name = '%s:%s' % ( addr.host, addr.port )
        self.logger = logging.getLogger()


    def connectionMade(self):
        self.trader = engine.Trader(self.matcher, self.name, self.transport)


    #def connectionLost(self, reason):
        #self.trader.cancelAll()


    def dataReceived(self, data):
        data = data.strip()
        if data:
            try:
                self.trader.handleMessage(data)
            except Exception:
                self.logger.exception('Trader %r raised error' % self.name)

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

