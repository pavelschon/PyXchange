# -*- coding: utf-8 -*-

##
# @file utils.py
# @brief Miscelangeous utilities for PyXchange
#
#

import collections
import time
import weakref

from . import engine


__all__ = (
    'BaseHandler',
    'DequeHandler'
    'TwistedHandler',
    'TestHandler',
    'ClientWrapper',
    'TraderWrapper'
)


class BaseHandler(object):
    """ Base interface for other handlers """

    def handleMessage(self, message):
        """ On message callback """

        raise NotImplementedError


    def disconnect(self):
        """ On disconnect callback """

        raise NotImplementedError


class DequeHandler(BaseHandler):
    """ Base handler for clients and traders """

    def __init__(self):
        self.messages = collections.deque()


    def handleMessage(self, message):
        """ On message callback """

        self.messages.append(message)


    def disconnect(self):
        """ On disconnect callback """

        pass


class TwistedHandler(BaseHandler):
    def __init__(self, lineHandler):
        """ Create weak reference to lineHandler """

        self.lineHandler = weakref.ref(lineHandler)


    def handleMessage(self, message):
        """ On message callback """

        lineHandler = self.lineHandler()
        if lineHandler is not None:
            lineHandler.sendLine(engine.json_dumps(message))


    def disconnect(self):
        """ On disconnect callback """

        lineHandler = self.lineHandler()
        if lineHandler is not None:
            lineHandler.transport.loseConnection()


class TestHandler(DequeHandler):
    """ Test transport provides some assertions """

    def __init__(self):
        """ Create fake connection, store timestamps for later assertions """

        super(TestHandler, self).__init__()

        self.connection = True

        self.t0 = time.time()
        self.t1 = self.t0 + 2


    def handleMessage(self, message):
        """ On message callback, assert type of message, compare timestamps """

        assert type(message) is dict
        assert self.connection, 'Connection is closed'

        if 'time' in message:
            assert message['time'] > self.t0
            assert message['time'] < self.t1
            message['time'] = 0

        super(TestHandler, self).handleMessage(message)


    def disconnect(self):
        """ Assert connection is open, close connection """

        assert self.connection, 'Connection is closed'

        self.connection = None


class ClientWrapper(object):
    """ Client wrapper with some assertions """

    def __init__(self, name, matcher):
        self.handler = TestHandler()
        self.client = engine.Client(matcher, name, self.handler)


    def __repr__(self):
        return '<ClientWrapper of %r>' % self.client


    def remove(self):
        self.client = None
        self.handler = None


    def clear(self):
        self.handler.messages.clear()


    def handleMessage(self, message):
        assert type(message) in (str, dict)

        self.client.handleMessage(message)


    def assertMessage(self, message):
        assert type(message) is dict
        assert message == self.handler.messages.popleft()


    def assertDisconnected(self):
        assert self.handler.connection is None, 'Connection is open'


class TraderWrapper(object):
    """ Trader wrapper with some assertions """

    def __init__(self, name, matcher):
        self.handler = TestHandler()
        self.trader = engine.Trader(matcher, name, self.handler)


    def __repr__(self):
        return '<TraderWrapper of %r>' % self.trader


    def remove(self):
        self.trader = None
        self.handler = None


    def clear(self):
        self.handler.messages.clear()


    def handleMessage(self, message):
        assert type(message) in (str, dict)

        self.trader.handleMessage(message)


    def assertMessage(self, message):
        assert type(message) is dict
        assert message == self.handler.messages.popleft()


    def assertDisconnected(self):
        assert self.handler.connection is None, 'Connection is open'


# EOF

