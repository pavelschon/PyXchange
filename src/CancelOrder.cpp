/**
 * @brief This module implements simulator of exchange
 * @file CancelOrder.cpp
 *
 */


#include "Matcher.hpp"
#include "Trader.hpp"
#include "Utils.hpp"


namespace pyxchange
{

namespace py = boost::python;


/**
 * @brief FIXME
 *
 */
void Matcher::cancelOrder( const TraderPtr& trader, const boost::python::dict& decoded )
{
    const orderId_t orderId = py::extract<const orderId_t>( decoded["orderId"] );

    if( ! trader->cancelOrder( orderId ) )
    {
        cancelOrderError( trader, decoded );
    }
    else
    {
        cancelOrderSuccess( trader, decoded );
    }
}


/**
 * @brief FIXME
 *
 */
void Matcher::cancelOrderSuccess( const TraderPtr& trader, const boost::python::dict& decoded )
{
    py::dict response;

    response["message"] = message::executionReport;
    response["report" ] = report::cancel;
    response["orderId"] = decoded["orderId"];

    // send response
    trader->writeData( response );
}


/**
 * @brief FIXME
 *
 */
void Matcher::cancelOrderError( const TraderPtr& trader, const boost::python::dict& decoded )
{
    const char* const text = "order does not exist";

    py::dict response;

    response["message"] = message::executionReport;
    response["report" ] = report::err;
    response["text"   ] = text;
    response["orderId"] = decoded["orderId"];

    // send response
    trader->writeData( response );

    PyErr_SetString( PyExc_ValueError, text );

    py::throw_error_already_set();
}


} /* namespace pyxchange */



/* EOF */

