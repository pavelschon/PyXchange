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

execute_process (
    COMMAND ${PYTHON_EXECUTABLE} -c "import distutils.sysconfig as cfg; print cfg.get_python_lib()"
    OUTPUT_VARIABLE PACKAGES_DIRECTORY OUTPUT_STRIP_TRAILING_WHITESPACE
)

# configure_file(
#     ${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in
#     ${CMAKE_CURRENT_BINARY_DIR}/setup.py
# )

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${PYTHON_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
)

add_library( engine SHARED
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


set_target_properties( engine
    PROPERTIES PREFIX ""
)


target_link_libraries ( engine
    ${Boost_LIBRARIES}
)


install(
    TARGETS engine
    DESTINATION ${PACKAGES_DIRECTORY}/pyxchange
    PERMISSIONS OWNER_READ GROUP_READ WORLD_READ
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/pyxchange
    DESTINATION ${PACKAGES_DIRECTORY}
    FILES_MATCHING PATTERN "*.py"
    PERMISSIONS OWNER_READ GROUP_READ WORLD_READ
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
    DESTINATION /
    FILES_MATCHING PATTERN "*.py"
    PERMISSIONS OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)


set( CPACK_GENERATOR "DEB" )
set( CPACK_PACKAGE_VERSION_MAJOR "0" )
set( CPACK_PACKAGE_VERSION_MINOR "1" )
set( CPACK_PACKAGE_VERSION_PATCH "0" )
set( CPACK_DEBIAN_PACKAGE_DESCRIPTION "PyXchange - simulator of an exchange" )
set( CPACK_DEBIAN_PACKAGE_MAINTAINER "Pavel Schön <pavel@schon.cz>" )
set( CPACK_DEBIAN_PACKAGE_DEPENDS "python (>= 2.7), python (<< 2.8), python-twisted (>= 14.0), libboost-python-dev (>=1.55)" )
set( CPACK_DEBIAN_PACKAGE_BUILD_DEPENDS "python-dev (>= 2.7), python-dev (<< 2.8), libboost-python-dev (>=1.55)" )

include(CPack)


# EOF
