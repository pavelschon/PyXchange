##
# @file utils.py
# @brief FIXME
#
#

import collections
import time


__all__ = (
    'Transport',
     'TestTransport',
    'ClientWrapper',
    'TraderWrapper'
)


class Transport(object):
    """ Base transport handler for client and trader """

    def __init__(self):
        self.messages = collections.deque()


    def writeData(self, message):
        """ On message callback """

        self.messages.append(message)


    def loseConnection(self):
        """ On disconnect callback """

        pass


class TestTransport(Transport):
    """ FIXME """

    def __init__(self):
        """ FIXME """

        super(TestTransport, self).__init__()

        self.connection = True

        self.t0 = time.time()
        self.t1 = self.t0 + 2


    def writeData(self, message):
        """ On message callback """

        assert type(message) is dict
        assert self.connection, 'Connection is closed'

        if 'time' in message:
            assert message['time'] > self.t0
            assert message['time'] < self.t1
            message['time'] = 0

        super(TestTransport, self).writeData(message)


    def loseConnection(self):
        """ FIXME """

        assert self.connection, 'Connection is closed'

        self.connection = None


class ClientWrapper(object):
    """ FIXME """
    def __init__(self, name, matcher):
        """ FIXME """

        self.matcher = matcher
        self.transport = TestTransport()
        self.client = matcher.getClient(name, self.transport)


    def __repr__(self):
        return '<ClientWrapper of %r>' % self.client


    def clear(self):
        """ Clear messages in the queue """

        self.transport.messages.clear()


    def handleMessageStr(self, message):
        """ FIXME """

        self.client.handleMessageStr(self.matcher, message)


    def handleMessageDict(self, message):
        """ FIXME """

        assert type(message) is dict
        self.client.handleMessageDict(self.matcher, message)


    def assertMessage(self, message):
        """ FIXME """

        assert type(message) is dict
        assert message == self.transport.messages.popleft()


    def assertDisconnected(self):
        """ FIXME """

        assert self.transport.connection is None, 'Connection is open'


class TraderWrapper(object):
    """ FIXME """

    def __init__(self, name, matcher):
        """ FIXME """

        self.matcher = matcher
        self.transport = TestTransport()
        self.trader = matcher.getTrader(name, self.transport)


    def __repr__(self):
        return '<TraderWrapper of %r>' % self.trader


    def clear(self):
        """ Clear messages in the queue """

        self.transport.messages.clear()


    def handleMessageStr(self, message):
        """ FIXME """

        self.trader.handleMessageStr(self.matcher, message)


    def handleMessageDict(self, message):
        """ FIXME """

        assert type(message) is dict
        self.trader.handleMessageDict(self.matcher, message)


    def assertMessage(self, message):
        """ FIXME """

        assert type(message) is dict
        assert message == self.transport.messages.popleft()


    def assertDisconnected(self):
        """ FIXME """

        assert self.transport.connection is None, 'Connection is open'


# EOF

