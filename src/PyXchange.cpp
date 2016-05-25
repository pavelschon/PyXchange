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

    class_<Client, ClientPtr, boost::noncopyable>( "Client", no_init )
        .def( "__init__", make_constructor( &make_shared_<Client, const object&> ) )
        .def( "write", &Client::writeString, args( "data" ) )
        ;

    class_<Trader, TraderPtr, boost::noncopyable>( "Trader", no_init )
        .def( "__init__", make_constructor( &make_shared_<Trader, const object&> ) )
        .def( "write", &Trader::writeString, args( "data" ) )
    ;

    class_<Matcher, boost::noncopyable>( "Matcher", no_init )
        .def( "__init__", make_constructor( &make_shared_<Matcher> ) )
        .def( "addTrader", &Trader::addTrader, args( "trader" ) )
        .def( "addClient", &Client::addClient, args( "client" ) )
        .def( "removeTrader", &Trader::removeTrader, args( "trader" ) )
        .def( "removeClient", &Client::removeClient, args( "client" ) )
        .def( "handleMessageStr", &Matcher::handleMessageStr, args( "trader", "data" ) )
        .def( "handleMessageDict", &Matcher::handleMessageDict, args( "trader", "data" ) )
    ;

    def( "json_dumps", &json_dumps<const char*> );
    def( "json_loads", &json_loads<const char*> );
}


/* EOF */

