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


namespace side
{

const boost::python::str buy  = "BUY";
const boost::python::str sell = "SELL";


} /* namespace side */


namespace report
{

const std::string new_   = "NEW";
const std::string cancel = "CANCELED";
const std::string fill   = "FILL";
const std::string err    = "ERROR";

} /* namespace report */


namespace strings
{

const std::string orderDoesNotExist     = "order does not exists";
const std::string orderAlreadyExist     = "order already exists";

const std::string traderAlreadyAdded    = "trader already added";
const std::string clientAlreadyAdded    = "client already added";

const std::string traderDoesNotExist    = "trader does not exist";
const std::string clientDoesNotExist    = "client does not exist";

const std::string jsonError             = "json decode error";

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

