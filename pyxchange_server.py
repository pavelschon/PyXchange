#!/usr/bin/env python2.7

from twisted.internet import reactor, protocol

import pyxchange
import logging
import optparse
import traceback
import sys



class ClientProtocol(protocol.Protocol):
    """ Market-data client protocol """

    def __init__(self, factory, addr, **kwargs):
        self.factory = factory
        self.matcher = factory.matcher
        self.name = '%s:%s' % ( addr.host, addr.port )
        self.disconnect = kwargs.get('disconnect', False)
        self.logger = logging.getLogger()


    def connectionMade(self):
        self.logger.info('Registering client %s', self.name)
        self.client = self.matcher.getClient(self.name, self.transport)


    def connectionLost(self, reason):
        logger.info('Unregistering client %s', self.name)

        self.matcher.removeClient(self.client)


    def dataReceived(self, data):
        if self.disconnect:
            logger.warning('Unexpected data on market-data interface, '
                           'force disconnect %s', self.name)

            self.transport.loseConnection()


class TraderProtocol(protocol.Protocol):
    """ Trader protocol of market participants """

    def __init__(self, factory, addr, **kwargs):
        self.factory = factory
        self.matcher = factory.matcher
        self.name = '%s:%s' % ( addr.host, addr.port )
        self.disconnect = kwargs.get('disconnect', False)
        self.logger = logging.getLogger()


    def connectionMade(self):
        self.logger.info('Registering trader %s', self.name)
        self.trader = self.matcher.getTrader(self.name, self.transport)


    def connectionLost(self, reason):
        logger.info('Unregistering trader %s', self.name)
        self.matcher.removeTrader(self.trader)


    def dataReceived(self, data):
        data = data.strip()
        if data:
            try:
                self.matcher.handleMessageStr(self.trader, data)
            except Exception:
                self.onException()


    def onException(self):
        self.logger.exception('Error on trading interface, trader %s' % self.name)

        if self.disconnect:
            logger.warning('Force disconnect %s', self.name)
            self.transport.loseConnection()


class ClientFactory(protocol.Factory):
    """ Factory for market-data client protocol """

    def __init__(self, matcher, **kwargs):
        self.matcher = matcher
        self.kwargs = kwargs


    def buildProtocol(self, addr):
        return ClientProtocol(self, addr, **self.kwargs)


class TraderFactory(protocol.Factory):
    """ Factory for Trader protocol """

    def __init__(self, matcher, **kwargs):
        self.matcher = matcher
        self.kwargs = kwargs


    def buildProtocol(self, addr):
        return TraderProtocol(self, addr, **self.kwargs)


def parse_options():
    parser = optparse.OptionParser(
        usage = 'usage: %prog [options]',
        add_help_option = True
    )

    parser.add_option( '--listen-private',
        action = 'store',
        dest = 'private',
        help = 'Listen on private (trading) interface',
        metavar = 'ip:port',
        default = '*:7001'
    )

    parser.add_option( '--listen-public',
        action = 'store',
        dest = 'public',
        help = 'Listen on public (market-data) interface',
        metavar = 'ip:port',
        default = '*:7002'
    )

    parser.add_option( '--disconnect',
        action = 'store_true',
        dest = 'disconnect',
        help = 'Disconnect trader on error',
        default = False
    )

    parser.add_option( '--smp',
        action = 'store_true',
        dest = 'smp',
        help = 'Enable self match prevention',
        default = False
    )

    parser.add_option( '--log',
        action = 'store',
        dest = 'log',
        metavar='file',
        help = 'Log filename',
        default = '-'
    )

    parser.add_option( '--log-format',
        action = 'store',
        dest = 'log_format',
        metavar='format',
        help = 'Log format',
        default = '%(asctime)s %(levelname)s %(message)s'
    )

    return parser.parse_args(args=None, values=None)


def parse_ip_port(string):
    private_ip, private_port = string.split(':')
    private_port = int(private_port)
    if private_ip == '*':
        private_ip = ''

    return private_ip, private_port


def getLoggingHandler(filename):
    return ( logging.StreamHandler(sys.stdout) if filename == '-' else
             logging.FileHandler(filename) )


if __name__ == '__main__':
    options, args = parse_options()

    formatter = logging.Formatter(options.log_format)
    handler = getLoggingHandler(options.log)
    handler.setFormatter(formatter)
    logger = logging.getLogger()
    logger.addHandler(handler)
    logger.setLevel(logging.INFO)

    private_ip, private_port = parse_ip_port(options.private)
    public_ip,  public_port  = parse_ip_port(options.public)

    matcher = pyxchange.Matcher(logger)

    trader_factory = TraderFactory(matcher, disconnect=options.disconnect)
    client_factory = ClientFactory(matcher, disconnect=options.disconnect)

    reactor.listenTCP(interface=private_ip, port=private_port, factory=trader_factory)
    reactor.listenTCP(interface=public_ip,  port=public_port,  factory=client_factory)

    logger.info('Listeting on %s (trading), %s (market-data)', options.private, options.public)

    reactor.run()


# EOF

