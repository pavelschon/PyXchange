/**
 * @brief This module implements simulator of exchange
 * @file CancelOrder.cpp
 *
 */


#include "OrderBook.hpp"
#include "Trader.hpp"
#include "Utils.hpp"


namespace pyxchange
{

namespace py = boost::python;


/**
 * @brief FIXME
 *
 */
void OrderBook::cancelOrder( const TraderPtr& trader, const boost::python::dict& decoded )
{
    const auto& orderId = py::extract<const orderId_t>( decoded["orderId"] );

    if( ! trader->cancelOrder( orderId ) )
    {
        PyErr_SetString( PyExc_ValueError, "order does not exist" );

        py::throw_error_already_set();
    }

    py::dict response;

    response["message"] = message::executionReport;
    response["report" ] = report::cancel;
    response["orderId"] = decoded["orderId"];

    // send response
    trader->writeData( response );
}


} /* namespace pyxchange */



/* EOF */

