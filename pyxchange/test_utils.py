##
# @file test_utils.py
# @brief FIXME
#
#

import collections
import time

__all__ = (
    'Transport',
    'TraderPair',
    'ClientPair'
)


class Transport(object):
    """ FIXME """

    def __init__(self):
        """ FIXME """
        self.messages = collections.deque()
        self.connection = True

        self.t0 = time.time()
        self.t1 = self.t0 + 2


    def clear(self):
        """ FIXME """

        self.messages.clear()


    def writeData(self, message):
        """ FIXME """

        assert type(message) is dict
        assert self.connection, 'Connection is closed'

        if 'time' in message:
            assert message['time'] > self.t0
            assert message['time'] < self.t1
            message['time'] = 0

        self.messages.append(message)


    def loseConnection(self):
        """ FIXME """

        assert self.connection, 'Connection is closed'

        self.connection = None


    def assertMessage(self, message):
        """ FIXME """

        assert message == self.messages.popleft()


    def assertDisconnected(self):
        assert self.connection is None, 'Connection is open'


def createTraderPair(name, matcher):
    """ FIXME """

    transport = Transport()
    trader = matcher.getTrader(name, transport)

    return TraderPair(trader, transport)


def createClientPair(name, matcher):
    """ FIXME """

    transport = Transport()
    client = matcher.getClient(name, transport)

    return ClientPair(client, transport)


TraderPair = collections.namedtuple('TraderPair', ('trader', 'transport'))
ClientPair = collections.namedtuple('ClientPair', ('client', 'transport'))

TraderPair.create = staticmethod(createTraderPair)
ClientPair.create = staticmethod(createClientPair)


# EOF

