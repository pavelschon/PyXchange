##
# @file setup.py
# @brief FIXME
#
#
import os

import distutils.sysconfig

from distutils.core import setup, Extension


def remove_strict_prototypes():
    cfg_vars = distutils.sysconfig.get_config_vars()

    for key, value in cfg_vars.iteritems():
        if type(value) == str:
            cfg_vars[key] = value.replace('-Wstrict-prototypes', '')

remove_strict_prototypes()

engine = Extension('engine',
    language = 'c++',
    extra_compile_args = [ '-Wall', '-pedantic', '-fPIC', '-std=c++14' ],
    include_dirs = ['/usr/include/python2.7'],
    libraries = [ 'boost_python-py27' ],
    sources = [
        'src/Logger.cpp',
        'src/Order.cpp',
        'src/BaseClient.cpp',
        'src/Client.cpp',
        'src/Trader.cpp',
        'src/Matcher.cpp',
        'src/OrderBook.cpp',
        'src/OrderBookAggr.cpp',
        'src/OrderBookAggrAll.cpp',
        'src/OrderBookExec.cpp',
        'src/OrderBookInsert.cpp',
        'src/OrderBookCancel.cpp',
        'src/OrderBookCancelAll.cpp',
        'src/OrderBookSelfMatch.cpp',
        'src/PyXchange.cpp',
    ],
)

setup (
    name = 'pyxchange',
    version = '0.1.0',
    description = 'This is a demo package',
    ext_modules = [ engine ]
)



# EOF

