/**
 * @brief This module implements simulator of exchange
 * @file pyxchange.cpp
 * 
 */

#include "PyXchangeFwd.hpp"
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

    class_<Client, ClientPtr, boost::noncopyable>( "Client", no_init )
        .def( "__repr__", &Client::toString )
        ;

    class_<Trader, TraderPtr, boost::noncopyable>( "Trader", no_init )
        .def( "__repr__", &Trader::toString )
        .def( "handleMessage", &Matcher::handleMessage<TraderPtr, std::string>, args( "matcher", "data" ) )
        .def( "handleMessage", &Matcher::handleMessage<TraderPtr, py::dict>, args( "matcher", "data" ) )
        .def( "createOrder",   &Matcher::handleCreateOrder, args( "matcher", "data" ) )
        .def( "cancelOrder",   &Matcher::handleCancelOrder, args( "matcher", "data" ) )
    ;

    class_<Matcher, boost::noncopyable>( "Matcher", no_init )
        .def( "__init__", make_constructor( &make_shared_<Matcher> ) )
        .def( "__init__", make_constructor( &make_shared_<Matcher, const object&> ) )
        .def( "getTrader",    &Matcher::getTrader, args( "name", "transport" ) )
        .def( "getClient",    &Matcher::getClient, args( "name", "transport" ) )
        .def( "removeTrader", &Matcher::removeTrader, args( "trader" ) )
        .def( "removeClient", &Matcher::removeClient, args( "client" ) )
    ;

    def( "json_dumps", &json::dumps<const std::string> );
    def( "json_loads", &json::loads<const std::string> );

    scope().attr( "maxJsonSize" ) = json::maxJsonSize; // read-only module-level constant
}


/* EOF */

