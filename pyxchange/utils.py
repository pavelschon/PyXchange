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


    def writeData(self, data):
        """ On message callback """

        raise NotImplementedError


    def loseConnection(self):
        """ On disconnect callback """

        pass


# EOF

