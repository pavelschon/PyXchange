/**
 * @brief This module implements simulator of exchange
 * @file PyXchange.cpp
 * 
 */

#include "PyXchange.hpp"
#include "client/Client.hpp"
#include "client/Trader.hpp"
#include "matcher/Matcher.hpp"
#include "orderbook/OrderBook.hpp"
#include "utils/Json.hpp"


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
    namespace py = boost::python;

    using namespace ::boost::python;
    using namespace ::pyxchange;

    const auto make_trader = &make_shared_<Trader,
        const MatcherPtr&, const std::string&, const object&>;

    class_<Trader, TraderPtr, boost::noncopyable>( "Trader", no_init )
        .def( "__init__",      make_constructor( make_trader ) )
        .def( "__str__",       &Trader::toString )
        .def( "ping",          &Trader::notifyPong )
        .def( "handleMessage", &Matcher::handleMessageJson, args( "data" ) )
        .def( "handleMessage", &Matcher::handleMessageDict, args( "data" ) )
        .def( "createOrder",   &Matcher::handleCreateOrder, args( "data" ) )
        .def( "marketOrder",   &Matcher::handleMarketOrder, args( "data" ) )
        .def( "cancelOrder",   &Matcher::handleCancelOrder, args( "data" ) )
        .def( "cancelAll",     &Matcher::handleCancelAll,   args( "data" ) )
    ;

    class_<Client, ClientPtr, boost::noncopyable>( "Client", no_init )
        .def( "__init__", make_constructor( &Matcher::makeClient ) )
        .def( "__str__",  &Client::toString )
    ;


    class_<Matcher, MatcherPtr, boost::noncopyable>( "Matcher", no_init )
        .def( "__init__", make_constructor( &make_shared_<Matcher> ) )
        .def( "__init__", make_constructor( &make_shared_<Matcher, const object&> ) )
    ;

    def( "json_dumps", &json::dumps<const std::string> );
    def( "json_loads", &json::loads<const std::string> );

    scope().attr( "maxJsonSize" ) = json::maxJsonSize; // read-only module-level constant
}


/* EOF */

