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
    const orderId_t orderId = py::extract<const orderId_t>( decoded[ keys::orderId ] );

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

    response[ keys::message ] = message::executionReport;
    response[ keys::report  ] = report::cancel;
    response[ keys::orderId ] = decoded[ keys::orderId ];

    // send response
    trader->writeData( response );
}


/**
 * @brief FIXME
 *
 */
void Matcher::cancelOrderError( const TraderPtr& trader, const boost::python::dict& decoded )
{
    py::dict response;

    response[ keys::message ] = message::executionReport;
    response[ keys::report  ] = report::err;
    response[ keys::text    ] = strings::orderDoesNotExist;
    response[ keys::orderId ] = decoded[ keys::orderId ];

    // send response
    trader->writeData( response );

    PyErr_SetString( PyExc_ValueError, strings::orderDoesNotExist );

    py::throw_error_already_set();
}


} /* namespace pyxchange */



/* EOF */

