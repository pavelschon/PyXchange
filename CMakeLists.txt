##
# @file CMakeLists.txt
# @brief Performance Monitor package.
#

cmake_minimum_required( VERSION 3.0 )

add_compile_options( -Wall )
add_compile_options( -pedantic )
add_compile_options( -fPIC )
add_compile_options( -std=c++14 )

set( CMAKE_VERBOSE_MAKEFILE OFF )

project( pyxchange CXX )

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    /usr/include/python2.7
)


add_library( pyxchange SHARED
    src/Logger.cpp
    src/Order.cpp
    src/BaseClient.cpp
    src/Client.cpp
    src/Trader.cpp
    src/Matcher.cpp
    src/OrderBook.cpp
    src/OrderBookAggr.cpp
    src/OrderBookAggrAll.cpp
    src/OrderBookExec.cpp
    src/OrderBookInsert.cpp
    src/OrderBookCancel.cpp
    src/OrderBookCancelAll.cpp
    src/OrderBookSelfMatch.cpp
    src/PyXchange.cpp
)


set_target_properties( pyxchange
    PROPERTIES PREFIX ""
)


target_link_libraries ( pyxchange
    boost_python-py27
)

add_executable(

set(CPACK_GENERATOR "DEB")


set( CPACK_GENERATOR "DEB" )
set( CPACK_PACKAGE_VERSION_MAJOR "0" )
set( CPACK_PACKAGE_VERSION_MINOR "1" )
set( CPACK_PACKAGE_VERSION_PATCH "0" )
set( CPACK_DEBIAN_PACKAGE_DESCRIPTION "PyXchange - simulator of an exchange" )
set( CPACK_DEBIAN_PACKAGE_MAINTAINER "Pavel Schön <pavel@schon.cz>" )
set( CPACK_DEBIAN_PACKAGE_DEPENDS "python (>= 2.7), python (<< 2.8), python-twisted (>= 14.0), libboost-python (>=1.55)" )
set( CPACK_DEBIAN_PACKAGE_BUILD_DEPENDS "python-dev (>= 2.7), python-dev (<< 2.8), libboost-dev (>=1.55)" )

include(CPack)


# EOF
