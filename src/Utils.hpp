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

const boost::python::str createOrder        = "createOrder";
const boost::python::str cancelOrder        = "cancelOrder";
const boost::python::str executionReport    = "executionReport";
const boost::python::str orderBook          = "orderbook";

} /* namespace message */


namespace side
{

const boost::python::str bid = "BUY";
const boost::python::str ask = "SELL";


} /* namespace side */


namespace report
{

const boost::python::str new_   = "NEW";
const boost::python::str cancel = "CANCELED";
const boost::python::str fill   = "FILL";
const boost::python::str err    = "ERROR";

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

const char* const message   = "message";
const char* const report    = "report";
const char* const price     = "price";
const char* const orderId   = "orderId";
const char* const quantity  = "quantity";
const char* const side      = "side";
const char* const text      = "text";

} /* namespace keys */


} /* namespace pyxchange */


#endif /* UTILS */


/* EOF */

