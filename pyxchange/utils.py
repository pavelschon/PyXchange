##
# @file utils.py
# @brief FIXME
#
#

import collections
import time

from . import engine


__all__ = (
    'Transport',
    'TestTransport',
    'ClientWrapper',
    'TraderWrapper'
)


class Transport(object):
    """ Base transport handler for clients and traders """

    def __init__(self):
        self.messages = collections.deque()


    def writeData(self, message):
        """ On message callback """

        self.messages.append(message)


    def loseConnection(self):
        """ On disconnect callback """

        pass


class TestTransport(Transport):
    """ Test transport provides some assertions """

    def __init__(self):
        """ Create fake connection, store timestamps for later assertions """

        super(TestTransport, self).__init__()

        self.connection = True

        self.t0 = time.time()
        self.t1 = self.t0 + 2


    def writeData(self, message):
        """ On message callback, assert type of message, compare timestamps """

        assert type(message) is dict
        assert self.connection, 'Connection is closed'

        if 'time' in message:
            assert message['time'] > self.t0
            assert message['time'] < self.t1
            message['time'] = 0

        super(TestTransport, self).writeData(message)


    def loseConnection(self):
        """ Assert connection is open, close connection """

        assert self.connection, 'Connection is closed'

        self.connection = None


class ClientWrapper(object):
    """ Client wrapper with some assertions """

    def __init__(self, name, matcher):
        self.transport = TestTransport()
        self.client = engine.Client(matcher, name, self.transport)


    def __repr__(self):
        return '<ClientWrapper of %r>' % self.client


    def remove(self):
        self.client = None
        self.transport = None


    def clear(self):
        self.transport.messages.clear()


    def handleMessage(self, message):
        assert type(message) in (str, dict)

        self.client.handleMessage(message)


    def assertMessage(self, message):
        assert type(message) is dict
        assert message == self.transport.messages.popleft()


    def assertDisconnected(self):
        assert self.transport.connection is None, 'Connection is open'


class TraderWrapper(object):
    """ Trader wrapper with some assertions """

    def __init__(self, name, matcher):
        self.transport = TestTransport()
        self.trader = engine.Trader(matcher, name, self.transport)


    def __repr__(self):
        return '<TraderWrapper of %r>' % self.trader


    def remove(self):
        self.trader = None
        self.transport = None


    def clear(self):
        self.transport.messages.clear()


    def handleMessage(self, message):
        assert type(message) in (str, dict)

        self.trader.handleMessage(message)


    def assertMessage(self, message):
        assert type(message) is dict
        assert message == self.transport.messages.popleft()


    def assertDisconnected(self):
        assert self.transport.connection is None, 'Connection is open'


# EOF

