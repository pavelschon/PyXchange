##
# @file test_utils.py
# @brief FIXME
#
#

from utils import Transport

import collections
import time

__all__ = (
    'TestTransport',
    'ClientWrapper',
    'TraderWrapper'
)


class TestTransport(Transport):
    """ FIXME """

    def __init__(self):
        """ FIXME """

        super(TestTransport, self).__init__()

        self.connection = True

        self.t0 = time.time()
        self.t1 = self.t0 + 2


    def clear(self):
        """ Clear messages in the queue """

        self.messages.clear()


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


    def assertMessage(self, message):
        """ FIXME """

        assert message == self.messages.popleft()


    def assertDisconnected(self):
        assert self.connection is None, 'Connection is open'



class ClientWrapper(object):
    def __init__(self, name, matcher):
        self.transport = TestTransport()
        self.client = matcher.getClient(name, self.transport)


class TraderWrapper(object):
    def __init__(self, name, matcher):
        self.transport = TestTransport()
        self.trader = matcher.getTrader(name, self.transport)



# EOF

