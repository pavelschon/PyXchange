#!/usr/bin/env python2.7
# -*- coding: utf-8 -*-

##
# @file pyxchange_server.py
# @brief Run Pyxchange as TCp server
#
# Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
#
#

import sys
import logging
import optparse

from twisted.internet import reactor

from pyxchange import engine, server


def parse_options():
    """ Parse command-line options """

    parser = optparse.OptionParser(
        usage = 'usage: %prog [options]',
        add_help_option = True
    )

    parser.add_option( '--listen-private-ext',
        action = 'store',
        dest = 'private2',
        help = 'Listen on extended private (trading) interface',
        metavar = 'ip:port',
        default = '*:7000'
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

    parser.add_option( '--format',
        action = 'store',
        dest = 'format',
        metavar='format',
        help = 'Log format',
        default = '%(asctime)s %(name)s %(levelname)s %(message)s'
    )

    parser.add_option( '--debug', '-d',
        action = 'store_true',
        dest = 'debug',
        metavar='file',
        help = 'Enable debug level',
        default = False
    )

    return parser.parse_args(args=None, values=None)


def get_ip_port_kwargs(ipString):
    """ Parse IP and port into kwargs suitable for reactor.listenTCP """

    ip, port = ipString.split(':')
    ip, port = ( '' if ip == '*' else ip ), int(port)

    return dict(interface=ip, port=port)


def get_logging_handler(filename):
    """ Create StremHandler or Filehandler """

    return ( logging.StreamHandler(sys.stdout) if filename == '-' else
             logging.FileHandler(filename) )


def serve_forever():
    """ Run the reactor """

    options, args = parse_options()

    formatter = logging.Formatter(options.format)

    handler = get_logging_handler(options.log)
    handler.setFormatter(formatter)

    logger = logging.getLogger(engine.logger)

    logger.addHandler(handler)
    logger.setLevel(logging.INFO)

    if options.debug:
        logger.setLevel(logging.DEBUG)
        logger.info('Debug level is enabled')

    matcher = engine.Matcher()

    reactor.listenTCP(factory=server.TraderFactory(matcher),    **get_ip_port_kwargs(options.private))
    reactor.listenTCP(factory=server.TraderExtFactory(matcher), **get_ip_port_kwargs(options.private2))
    reactor.listenTCP(factory=server.ClientFactory(matcher),    **get_ip_port_kwargs(options.public))

    logger.info('Listeting on %s (ext trading)', options.private2)
    logger.info('Listeting on %s (trading)',     options.private)
    logger.info('Listeting on %s (market-data)', options.public)

    reactor.run()


if __name__ == '__main__':
    serve_forever()


# EOF

