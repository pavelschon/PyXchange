##
# @file CMakeLists.txt
# @brief Performance Monitor package.
#

cmake_minimum_required( VERSION 3.0 )

add_compile_options( -Wall )
add_compile_options( -pedantic )
add_compile_options( -fPIC )
add_compile_options( -std=c++14 )

set( CMAKE_VERBOSE_MAKEFILE ON )

project( pyxchange CXX )

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    /usr/include/python2.7
)


add_library( pyxchange SHARED
    src/Client.cpp
    src/Trader.cpp
    src/Matcher.cpp
    src/PyXchange.cpp

    src/orderbook/Order.cpp
    src/orderbook/OrderBook.cpp
    src/orderbook/CreateOrder.cpp
)


target_link_libraries ( pyxchange
    boost_python-py27
    python2.7
)


set_target_properties( pyxchange
    PROPERTIES PREFIX ""
)


target_link_libraries ( pyxchange
    boost_python-py27
    python2.7
)


# EOF
