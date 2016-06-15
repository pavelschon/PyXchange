/**
 * @brief   Static constants, log messagess, keys
 * @file    Constants.hpp
 *
 */

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include "PyXchange.hpp"


namespace pyxchange
{


namespace format
{

namespace f0
{

const boost::format wrongSide( "order has wrong side" );
const boost::format wrongOrderId( "order has wrong order id" );
const boost::format wrongPrice( "order has wrong price" );
const boost::format wrongQuantity( "order has wrong quantity" );

const boost::format orderDoesNotExist( "order does not exists" );
const boost::format orderAlreadyExist( "order already exists" );

const boost::format logMatcherReady( "Matcher is ready" );
const boost::format unknownMessage( "unknown message" );

const boost::format selfMatch( "self-match rejected" );

const boost::format errNoHandleMessage( "object has no attribute 'handleMessage'" );
const boost::format errNoDisconnect( "object has no attribute 'disconnect'" );

} /* namespace f0 */


namespace f1
{

const boost::format logJsonDecodeError( "%|| JSON decode error" );
const boost::format logMalformedMessage( "%|| sent malformed message" );
const boost::format logUnknownMessage( "%|| sent unknown message" );

const boost::format logWrongSide( "Trader %|| inserting order with invalid side" );
const boost::format logWrongOrderId( "Trader %|| inserting order with invalid order id" );
const boost::format logWrongPrice( "Trader %|| inserting order with invalid price" );
const boost::format logWrongQuantity( "Trader %|| inserting order with invalid quantity" );

} /* namespace f1 */


namespace f2
{

const boost::format logJsonTooLong( "%|| JSON too long (%|| bytes)" );
const boost::format logTraderAddedOrder( "Trader %|| added %||" );
const boost::format logTraderCanceledOne( "Trader %|| cancelled %||" );
const boost::format logOrderAlreadyExist( "Trader %|| adding order id %||, but it already exists" );
const boost::format logOrderDoesNotExist( "Trader %|| canceling order id %||, but it does not exists" );
const boost::format logExecution( "Execution %||@%||" );
const boost::format marketOrder( "market order %||:%||" );

} /* namespace f2 */


namespace f3
{

const boost::format order( "order %||:%||@%||" );
const boost::format logTraderCanceledAll( "Trader %|| cancelled %|| bid orders, %|| ask orders" );

} /* namespace f3 */


} /* namespace format */


namespace message
{

/**
 * @brief Convert string into wstring
 * @brief string
 * @return wstring
 *
 */
inline std::wstring string2wstring( const std::string& str )
{
    return std::wstring( str.begin(), str.end() );
}

const std::string ping              = "ping";
const std::string pong              = "pong";

const std::string executionReport   = "executionReport";
const std::string orderBook         = "orderbook";
const std::string error             = "error";
const std::string trade             = "trade";

const std::string  createOrder      = "createOrder";
const std::string  marketOrder      = "marketOrder";
const std::string  cancelOrder      = "cancelOrder";
const std::string  cancelAll        = "cancelAll";

const std::wstring wPing( string2wstring( ping ) );
const std::wstring wCreateOrder( string2wstring( createOrder ) );
const std::wstring wMarketOrder( string2wstring( marketOrder ) );
const std::wstring wCancelOrder( string2wstring( cancelOrder ) );
const std::wstring wCancelAll( string2wstring( cancelAll ) );

const auto all = { wPing, wCreateOrder, wMarketOrder, wCancelOrder, wCancelAll };


} /* namespace message */


namespace report
{


const std::string new_   = "NEW";
const std::string cancel = "CANCELED";
const std::string fill   = "FILL";


} /* namespace report */


namespace keys
{


const std::string message   = "message";
const std::string report    = "report";
const std::string price     = "price";
const std::string orderId   = "orderId";
const std::string quantity  = "quantity";
const std::string side      = "side";
const std::string text      = "text";
const std::string time      = "time";
const std::string type      = "type";


} /* namespace keys */


} /* namespace pyxchange */


#endif /* CONSTANTS_HPP */


/* EOF */


