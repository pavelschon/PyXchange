#!/usr/bin/env python2.7
# -*- coding: utf-8 -*-

##
# @file server.py
# @brief Factories and protocols for Twisted
#
#

import logging

from twisted.internet import protocol
from twisted.protocols import basic

from . import engine
from . import utils


__all__ = (
    'BaseProtocol',
    'BaseFactory',
    'ClientProtocol',
    'ClientFactory',
    'TraderProtocol',
    'TraderFactory',
    'TraderExtProtocol',
    'TraderExtFactory'
)


logger = logging.getLogger(engine.logger)


class BaseProtocol(basic.LineOnlyReceiver):
    """ Base protocol """

    delimiter = '\n'
    prefix = None

    def __init__(self, matcher, addr):
        self.matcher = matcher
        self.name = '%s@%s:%s' % ( self.prefix, addr.host, addr.port )
        self.handler = utils.TwistedHandler(self)


class ClientProtocol(BaseProtocol):
    """ Market-data protocol """

    prefix = 'Client'

    def connectionMade(self):
        self.client = engine.Client(self.matcher, self.name, self.handler)


    def connectionLost(self, reason):
        self.client.logDisconnect()


    def dataReceived(self, data):
        logger.warning('%s unexpected data received, disconnecting', self.name)

        self.transport.loseConnection()


class TraderProtocol(BaseProtocol):
    """ Trading protocol of market participants """

    prefix = 'Trader'

    def connectionMade(self):
        self.trader = engine.Trader(self.matcher, self.name, self.handler)


    def connectionLost(self, reason):
        self.trader.logDisconnect()


    def lineReceived(self, message):
        try:
            self.trader.handleMessage(message)
        except Exception:
            logger.exception('%s error' % self.name)

            self.transport.loseConnection()


class TraderExtProtocol(TraderProtocol):
    """ Extended trading protocol of market participants """

    prefix = 'XTrader'

    def connectionLost(self, reason):
        self.trader.cancelAll()
        self.trader.logDisconnect()


class BaseFactory(protocol.Factory):
    """ Base factory for trading and market data protocols """

    protocol = BaseProtocol


    def __init__(self, matcher):
        self.matcher = matcher


    def buildProtocol(self, addr):
        return self.protocol(self.matcher, addr)


class ClientFactory(BaseFactory):
    """ Factory for market-data protocol """

    protocol = ClientProtocol


class TraderFactory(BaseFactory):
    """ Factory for trading protocol """

    protocol = TraderProtocol


class TraderExtFactory(BaseFactory):
    """ Factory for extended trading protocol """

    protocol = TraderExtProtocol


# EOF

