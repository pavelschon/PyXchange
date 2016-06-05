##
# @file test_utils.py
# @brief FIXME
#
#

import collections

import engine

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


    def clear(self):
        """ FIXME """

        self.messages.clear()


    def write(self, data):
        """ FIXME """

        assert type(data) is str
        assert self.connection, 'Connection is closed'

        for message in data.split('\n'):
            if message:
                message = engine.json_loads(message)
                if 'time' in message: message['time'] = 0
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

