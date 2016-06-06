##
# @file utils.py
# @brief FIXME
#
#


import collections


__all__ = (
    'Transport',
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


# EOF

