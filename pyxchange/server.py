#!/usr/bin/env python2.7
# -*- coding: utf-8 -*-

##
# @file server.py
# @brief Factories and protocols for Twisted
#
#

import logging

from twisted.internet import protocol

from . import engine

__all__ = (
    'BaseFactory',
    'ClientProtocol',
    'ClientFactory',
    'TraderProtocol'
    'TraderFactory',
    'TraderExtProtocol',
    'TraderExtFactory'
)


class ClientProtocol(protocol.Protocol):
    """ Market-data protocol """

    def __init__(self, matcher, addr):
        self.matcher = matcher
        self.name = '%s:%s' % ( addr.host, addr.port )
        self.logger = logging.getLogger()


    def connectionMade(self):
        self.client = engine.Client(self.matcher, self.name, self.transport)


class TraderProtocol(protocol.Protocol):
    """ Trading protocol of market participants """

    def __init__(self, matcher, addr):
        self.matcher = matcher
        self.name = '%s:%s' % ( addr.host, addr.port )
        self.logger = logging.getLogger()


    def connectionMade(self):
        self.trader = engine.Trader(self.matcher, self.name, self.transport)


    def dataReceived(self, data):
        data = data.strip()
        if data:
            try:
                self.trader.handleMessage(data)
            except Exception:
                self.logger.exception('Trader %s raised error' % self.name)

                self.transport.loseConnection()


class TraderExtProtocol(TraderProtocol):
    """ Extended trading protocol of market participants """

    def connectionLost(self, reason):
        self.trader.cancelAll()


class BaseFactory(protocol.Factory):
    """ Base factory for trading and market data protocols """

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

