/**
 * @brief This module implements simulator of exchange
 * @file Utils.hpp
 *
 */

#ifndef UTILS
#define UTILS

#include "PyXchangeFwd.hpp"


namespace pyxchange
{


namespace message
{

const std::string createOrder        = "createOrder";
const std::string cancelOrder        = "cancelOrder";
const std::string executionReport    = "executionReport";
const std::string orderBook          = "orderbook";

} /* namespace message */


namespace format
{

const boost::format client( "<Client %||>" );
const boost::format trader( "<Trader %||>" );
const boost::format clientDoesNotExist( "%|| does not exists" );
const boost::format traderDoesNotExist( "%|| does not exists" );
const boost::format traderAddedOrder( "%|| added %|| order id %|| at price %|| of quantity %||" );
const boost::format traderCanceledAll( "%|| cancelled all %|| bid orders, %|| ask orders" );
const boost::format traderSelfMatch( "%|| self-match prevention rejected %|| order id %|| "
                                     "matching with %|| order id %|| at price %||" );
const boost::format logOrderAlreadyExist( "%|| adding order id %||, but it already exists" );
const boost::format logOrderDoesNotExist( "%|| canceling order id %||, but it does not exists" );
const boost::format logMatcherReady( "Matcher is ready" );
const boost::format logGetClient( "%|| created" );
const boost::format logRemoveClient( "%|| removed" );


} /* namespace message */


namespace side
{

const std::string buy   = "BUY";
const std::string sell  = "SELL";

const std::string bid   = "bid";
const std::string ask   = "ask";

const side_t bid_       = 1;
const side_t ask_       = 2;


/**
 * @brief FIXME
 *
 */
inline side_t opposite( const side_t side_ )
{
    switch( side_ )
    {
        case bid_: return ask_;
        case ask_: return bid_;
        default:   throw;
    }
}


/**
 * @brief FIXME
 *
 */
inline std::string toBuySell( const side_t side_ )
{
    switch( side_ )
    {
        case bid_: return buy;
        case ask_: return sell;
        default:   throw;
    }
}


/**
 * @brief FIXME
 *
 */
inline std::string toBidAsk( const side_t side_ )
{
    switch( side_ )
    {
        case bid_: return bid;
        case ask_: return ask;
        default:   throw;
    }
}


class WrongSide: public std::exception
{

};


} /* namespace side */


namespace strings
{

const std::string orderDoesNotExist     = "order does not exists";
const std::string orderAlreadyExist     = "order already exists";
const std::string orderInvalid          = "order is invalid";
const std::string orderSelfMatch        = "order self-match rejected";

const std::string unknownMessage        = "unknown message";
const std::string unknownSide           = "unknown side";

} /* namespace strings */



namespace keys
{

const std::string message   = "message";
const std::string report    = "report";
const std::string price     = "price";
const std::string orderId   = "orderId";
const std::string quantity  = "quantity";
const std::string side      = "side";
const std::string text      = "text";

} /* namespace keys */


} /* namespace pyxchange */


#endif /* UTILS */


/* EOF */

