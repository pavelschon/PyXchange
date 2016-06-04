#!/usr/bin/env python2.7
##
# @file pyxchange_server.py
# @brief FIXME
#
#

import sys
import logging
import optparse
import pyxchange

from twisted.internet import reactor


def parse_options():
    """ FIXME """
    
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


def parse_IP_address(string):
    """ FIXME """

    private_ip, private_port = string.split(':')
    private_port = int(private_port)
    if private_ip == '*':
        private_ip = ''

    return private_ip, private_port


def get_logging_handler(filename):
    """ FIXME """

    return ( logging.StreamHandler(sys.stdout) if filename == '-' else
             logging.FileHandler(filename) )


def serve_forever():
    """ FIXME """

    options, args = parse_options()

    formatter = logging.Formatter(options.log_format)

    handler = get_logging_handler(options.log)
    handler.setFormatter(formatter)

    logger = logging.getLogger()
    logger.addHandler(handler)
    logger.setLevel(logging.INFO)

    private_ip, private_port = parse_IP_address(options.private)
    public_ip,  public_port  = parse_IP_address(options.public)

    matcher = pyxchange.engine.Matcher(logger)

    trader_factory = pyxchange.server.TraderFactory(matcher)
    client_factory = pyxchange.server.ClientFactory(matcher)

    reactor.listenTCP(interface=private_ip, port=private_port, factory=trader_factory)
    reactor.listenTCP(interface=public_ip,  port=public_port,  factory=client_factory)

    logger.info('Listeting on %s (trading)', options.private)
    logger.info('Listeting on %s (market-data)', options.public)

    reactor.run()


if __name__ == '__main__':
    serve_forever()


# EOF

