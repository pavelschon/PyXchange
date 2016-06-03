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


# EOF
