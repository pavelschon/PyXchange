#!/usr/bin/env python

import os
import sys

from twisted.internet import reactor, protocol

program = os.path.dirname(__file__) + '/server_process.py'
program_args = [ program ] + sys.argv[1:]


class PyCapWorkerProcess(protocol.ProcessProtocol):
    def __init__(self, parent):
        self.parent = parent

        reactor.spawnProcess(self, program, args=program_args, env=os.environ)


    def outReceived(self, data):
        self.parent.transport.write(data)


    def errReceived(self, data):
        print data


    def processEnded(self, reason):
        print reason
        self.parent.transport.loseConnection()


class PyCapWorker(protocol.Protocol):
    def __init__(self, factory):
        self.factory = factory

        self.process = PyCapWorkerProcess(self)


    def dataReceived(self, data):
        self.process.transport.write(data)


    def connectionLost(self, reason):
        self.factory.workers.append(self)
        #self.process.transport.closeStdin()


class PyCapFactory(protocol.Factory):
    workers = []


    def buildProtocol(self, addr):
        try:
            worker = self.workers.pop()
        except IndexError:
            return PyCapWorker(self)

        return worker


reactor.listenTCP(8001, PyCapFactory())

reactor.run()


# EOF

