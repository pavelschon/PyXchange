#!/usr/bin/env python2.7
# -*- coding: utf-8 -*-

##
# @file setup.py
# @brief FIXME
#
#

import glob
import distutils.sysconfig

from distutils.core import setup, Extension


def remove_unwanted_options():
    cfg_vars = distutils.sysconfig.get_config_vars()

    for key, value in cfg_vars.iteritems():
        if type(value) == str and cfg_vars[key].startswith('-'):
            cfg_vars[key] = '' #value.replace('-Wstrict-prototypes', '')


remove_unwanted_options()

engine = Extension('pyxchange.engine',
    language = 'c++',
    extra_compile_args = [ '-Wall', '-pedantic', '-fPIC', '-std=c++14' ],
    libraries = [ 'boost_python-py27' ],
    include_dirs = [ '/usr/include/python2.7', 'src' ],
    sources = (
        glob.glob('src/*.cpp') +
        glob.glob('src/logger/*.cpp') +
        glob.glob('src/client/*.cpp') +
        glob.glob('src/matcher/*.cpp')
        glob.glob('src/order/*.cpp')
        glob.glob('src/orderbook/*.cpp')
    )
)

setup(
    name = 'pyxchange',
    version = '0.1.0',
    description = 'PyXchange - simulator of limit orderbook',
    url = 'https://github.com/pavelschon/PyXchange.git',
    author ='Pavel Schön',
    author_email = 'pavel@schon.cz',
    requires = [ 'twisted' ],
    scripts = glob.glob('bin/*.py'),
    ext_modules = [ engine ],
    py_modules = [
        'pyxchange.server',
        'pyxchange.smoketest',
        'pyxchange.test_utils'
    ],
)


# EOF

