/**
 * @brief This module implements simulator of exchange
 * @file Constants.hpp
 *
 */

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include "PyXchangeFwd.hpp"


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

} /* namespace f0 */


namespace f1
{

const boost::format client( "<Client %||>" );
const boost::format trader( "<Trader %||>" );

const boost::format logGetClient( "%|| created" );
const boost::format logRemoveClient( "%|| removed" );

const boost::format clientDoesNotExist( "%|| does not exists" );
const boost::format traderDoesNotExist( "%|| does not exists" );

const boost::format jsonDecodeError( "%|| JSON decode error" );
const boost::format logMalformedMessage( "%|| sent malformed message" );
const boost::format logUnknownMessage( "%|| sent unknown message" );

const boost::format logWrongSide( "%|| inserting order with invalid side" );
const boost::format logWrongOrderId( "%|| inserting order with invalid order id" );
const boost::format logWrongPrice( "%|| inserting order with invalid price" );
const boost::format logWrongQuantity( "%|| inserting order with invalid quantity" );

} /* namespace f1 */


namespace f2
{

const boost::format logOrderAlreadyExist( "%|| adding order id %||, but it already exists" );
const boost::format logOrderDoesNotExist( "%|| canceling order id %||, but it does not exists" );

} /* namespace f2 */


namespace f3
{

const boost::format traderCanceledOne( "%|| cancelled %|| order id %||" );
const boost::format traderCanceledAll( "%|| cancelled all %|| bid orders, %|| ask orders" );

} /* namespace f3 */


namespace f5
{

const boost::format traderAddedOrder( "%|| added %|| order id %|| at price %|| of quantity %||" );

} /* namespace f5 */


namespace f6
{

const boost::format logSelfMatch( "%|| self-match prevention rejected %|| order id %|| "
                                   "matching with %|| order id %|| at price %||" );
} /* namespace f6 */


} /* namespace format */


namespace message
{

const std::string executionReport   = "executionReport";
const std::string orderBook         = "orderbook";
const std::string error             = "error";
const std::string trade             = "trade";

const std::string  createOrder      = "createOrder";
const std::string  cancelOrder      = "cancelOrder";

const std::wstring wCreateOrder( createOrder.begin(), createOrder.end() );
const std::wstring wCancelOrder( cancelOrder.begin(), cancelOrder.end() );

const auto all = { wCreateOrder, wCancelOrder };


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


namespace attr
{

const char* const loseConnection    = "loseConnection";
const char* const write             = "write";

}


} /* namespace pyxchange */


#endif /* CONSTANTS_HPP */


/* EOF */


