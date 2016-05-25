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

const char* const orderDoesNotExist     = "order does not exists";
const char* const orderAlreadyExist     = "order already exists";

const char* const traderAlreadyAdded    = "trader already added";
const char* const clientAlreadyAdded    = "client already added";

const char* const traderDoesNotExist    = "trader does not exist";
const char* const clientDoesNotExist    = "client does not exist";

const char* const jsonError             = "json decode error";

const char* const unknownMessage        = "unknown message";
const char* const unknownSide           = "unknown side";

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


const auto json = boost::python::import( "json" );

/**
 * @brief FIXME
 *
 */
template<typename T>
inline boost::python::object json_loads( T value )
{
    return json.attr( "loads" )( value );
}


/**
 * @brief FIXME
 *
 */
template<typename T>
inline T json_dumps( const boost::python::object& obj )
{
    return boost::python::extract<T>( json.attr( "dumps" )( obj ) );
}


} /* namespace pyxchange */


#endif /* UTILS */


/* EOF */

