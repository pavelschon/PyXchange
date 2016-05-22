/**
 * @brief This module implements simulator of exchange
 * @file pyxchange.cpp
 * 
 */

#include "PyXchangeFwd.hpp"
#include "Client.hpp"
#include "Trader.hpp"
#include "Matcher.hpp"
#include "Utils.hpp"

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include <boost/utility.hpp>

#include <memory>


/**
 * @brief FIXME
 *
 */
template<typename T, typename... Params>
std::shared_ptr<T> make_shared_( Params... parameters )
{
    return std::make_shared<T>( parameters... );
}


BOOST_PYTHON_MODULE( pyxchange )
{
    using namespace ::boost::python;
    using namespace ::pyxchange;

    class_<Client, ClientPtr, boost::noncopyable>( Client::name, no_init )
        .def( "__init__", make_constructor( &make_shared_<Client, const object&> ) )
        .def( "write", &Client::writeString )
        ;

    class_<Trader, TraderPtr, boost::noncopyable>( Trader::name, no_init )
        .def( "__init__", make_constructor( &make_shared_<Trader, const object&> ) )
        .def( "write", &Trader::writeString, args( "data" ) )
    ;

    class_<Matcher, MatcherPtr, boost::noncopyable>( Matcher::name, no_init )
        .def( "__init__", make_constructor( &make_shared_<Matcher> ) )
        .def( "addTrader", &Matcher::addTrader, args( "trader" ) )
        .def( "addClient", &Matcher::addClient, args( "client" ) )
        .def( "removeTrader", &Matcher::removeTrader, args( "trader" ) )
        .def( "removeClient", &Matcher::removeClient, args( "client" ) )
        .def( "handleMessageStr", &Matcher::handleMessageStr, args( "trader", "data" ) )
        .def( "handleMessageDict", &Matcher::handleMessageDict, args( "trader", "data" ) )
    ;

    def( "json_dumps", &json_dumps<const char*> );
    def( "json_loads", &json_loads<const char*> );
}


/* EOF */

