#!/usr/bin/env python
##
# @file pyxchange_example.py
# @brief FIXME
#
#

__all__ = (
    'Transport',
)


class Transport(object):
    """ Output handler for client and trader """

    def __init__(self):
        self.messages = collections.deque()


    def writeData(self, data):
        print data


# EOF

