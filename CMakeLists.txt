##
# @file CMakeLists.txt
# @brief Performance Monitor package.
#

cmake_minimum_required( VERSION 3.0 )

project( pyxchange CXX )

set( CMAKE_VERBOSE_MAKEFILE OFF )

add_compile_options( -Wall )
add_compile_options( -pedantic )
add_compile_options( -fPIC )
add_compile_options( -std=c++14 )

find_package( PythonLibs   "2.7" REQUIRED )
find_package( PythonInterp "2.7" REQUIRED )
find_package( Boost COMPONENTS python REQUIRED )

set( PythonPkgPathCmd "import distutils.sysconfig as cfg; print(cfg.get_python_lib())" )

execute_process (
    COMMAND ${PYTHON_EXECUTABLE} -c "${PythonPkgPathCmd}"
    OUTPUT_VARIABLE PythonPkgPath OUTPUT_STRIP_TRAILING_WHITESPACE
)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${PYTHON_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
)

add_library( engine SHARED
    src/PyXchange.cpp
    src/Logger.cpp
    src/Matcher.cpp
    src/MatcherApi.cpp
    src/client/BaseClient.cpp
    src/client/Client.cpp
    src/client/Trader.cpp
    src/orderbook/Order.cpp
    src/orderbook/OrderBook.cpp
    src/orderbook/OrderBookAggr.cpp
    src/orderbook/OrderBookAggrAll.cpp
    src/orderbook/OrderBookExec.cpp
    src/orderbook/OrderBookInsert.cpp
    src/orderbook/OrderBookCancel.cpp
    src/orderbook/OrderBookCancelAll.cpp
    src/orderbook/OrderBookSelfMatch.cpp
)

set_target_properties( engine PROPERTIES PREFIX "" )

target_link_libraries ( engine ${Boost_LIBRARIES} )

install(
    TARGETS engine
    DESTINATION ${PythonPkgPath}/pyxchange
    PERMISSIONS OWNER_READ GROUP_READ WORLD_READ
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/pyxchange
    DESTINATION ${PythonPkgPath}
    FILES_MATCHING PATTERN "*.py"
    PERMISSIONS OWNER_READ GROUP_READ WORLD_READ
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/examples
    DESTINATION /usr/share/doc/pyxchange
    FILES_MATCHING PATTERN "*.py"
    PERMISSIONS OWNER_READ GROUP_READ WORLD_READ
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
    DESTINATION /usr
    FILES_MATCHING PATTERN "*.py"
    PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)

set( CPACK_GENERATOR "DEB" )

set( CPACK_PACKAGE_VERSION_MAJOR "0" )
set( CPACK_PACKAGE_VERSION_MINOR "1" )
set( CPACK_PACKAGE_VERSION_PATCH "0" )

set( CPACK_DEBIAN_PACKAGE_DESCRIPTION "PyXchange - simulator of limit orderbook" )
set( CPACK_DEBIAN_PACKAGE_MAINTAINER "Pavel Schön <pavel@schon.cz>" )
set( CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/pavelschon/PyXchange.git")
set( CPACK_DEBIAN_PACKAGE_DEPENDS "python (>= 2.7), python (<< 2.8), python-twisted (>= 14.0), libboost-python${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION}" )
set( CPACK_DEBIAN_PACKAGE_BUILD_DEPENDS "python-dev (>= 2.7), python-dev (<< 2.8), libboost-all-dev" )

include(CPack)

# EOF

