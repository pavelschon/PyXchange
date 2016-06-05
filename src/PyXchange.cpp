/**
 * @brief This module implements simulator of exchange
 * @file pyxchange.cpp
 * 
 */

#include "PyXchangeFwd.hpp"
#include "Client.hpp"
#include "Trader.hpp"
#include "Matcher.hpp"
#include "OrderBook.hpp"
#include "Json.hpp"


/**
 * @brief FIXME
 *
 */
template<typename T, typename... Params>
std::shared_ptr<T> make_shared_( Params... parameters )
{
    return std::make_shared<T>( parameters... );
}


BOOST_PYTHON_MODULE( engine )
{
    using namespace ::boost::python;
    using namespace ::pyxchange;

    class_<Client, ClientPtr, boost::noncopyable>( "Client", no_init )
        .def( "__repr__", &Client::toString )
        .def( "write", &Client::writeString, args( "data" ) )
        ;

    class_<Trader, TraderPtr, boost::noncopyable>( "Trader", no_init )
        .def( "__repr__", &Trader::toString )
        .def( "write", &Trader::writeString, args( "data" ) )
    ;

    class_<Matcher, boost::noncopyable>( "Matcher", no_init )
        .def( "__init__", make_constructor( &make_shared_<Matcher> ) )
        .def( "__init__", make_constructor( &make_shared_<Matcher, const object&> ) )
        .def( "getTrader", &Matcher::getTrader, args( "name", "transport" ) )
        .def( "getClient", &Matcher::getClient, args( "name", "transport" ) )
        .def( "removeTrader", &Matcher::removeTrader, args( "trader" ) )
        .def( "removeClient", &Matcher::removeClient, args( "client" ) )
        .def( "handleMessageStr", &Matcher::handleMessageStr, args( "trader", "data" ) )
        .def( "handleMessageDict", &Matcher::handleMessageDict, args( "trader", "data" ) )
    ;

    def( "json_dumps", &json::dumps<const std::string> );
    def( "json_loads", &json::loads<const std::string> );
}


/* EOF */

