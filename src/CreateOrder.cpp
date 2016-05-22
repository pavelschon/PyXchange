/**
 * @brief This module implements simulator of exchange
 * @file CreateOrder.cpp
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
void OrderBook::createOrder( const TraderPtr& trader, const boost::python::dict& decoded )
{
    const auto& result = Trader::insertOrder( trader, decoded );

    if( !result.second )
    {
        createOrderError( trader, result.first );

        throw;
    }
    else if( result.first->side == side::bid )
    {
        createOrderSuccess( trader, result.first );
        handleBidExecution( trader, result.first );

        if( result.first->quantity )
        {
            bidOrders.insert( result.first );
        }
    }
    else if( result.first->side == side::ask )
    {
        createOrderSuccess( trader, result.first );
        handleAskExecution( trader, result.first );

        if( result.first->quantity )
        {
            askOrders.insert( result.first );
        }
    }
}


/**
 * @brief FIXME
 *
 */
void OrderBook::createOrderSuccess( const TraderPtr& trader, const OrderPtr& order )
{
    py::dict response;

    response["message"] = message::executionReport;
    response["report" ] = report::new_;
    response["orderId"] = order->orderId;

    // send response
    trader->writeData( response );
}



/**
 * @brief FIXME
 *
 */
void OrderBook::createOrderError( const TraderPtr& trader, const OrderPtr& order )
{
    const char* const text = "order already exists";

    py::dict response;

    response["message"] = message::executionReport;
    response["report" ] = report::err;
    response["text"   ] = text;
    response["orderId"] = order->orderId;

    // send response
    trader->writeData( response );

    PyErr_SetString( PyExc_ValueError, text );

    py::throw_error_already_set();
}


} /* namespace pyxchange */



/* EOF */

