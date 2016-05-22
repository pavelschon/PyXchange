/**
 * @brief This module implements simulator of exchange
 * @file CreateOrder.cpp
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
void Matcher::createOrder( const TraderPtr& trader, const boost::python::dict& decoded )
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
void Matcher::createOrderSuccess( const TraderPtr& trader, const OrderPtr& order )
{
    py::dict response;

    response[ keys::message ] = message::executionReport;
    response[ keys::report  ] = report::new_;
    response[ keys::orderId ] = order->orderId;

    // send response
    trader->writeData( response );
}



/**
 * @brief FIXME
 *
 */
void Matcher::createOrderError( const TraderPtr& trader, const OrderPtr& order )
{
    py::dict response;

    response[ keys::message ] = message::executionReport;
    response[ keys::report  ] = report::err;
    response[ keys::text    ] = strings::orderAlreadyExist;
    response[ keys::orderId ] = order->orderId;

    // send response
    trader->writeData( response );

    PyErr_SetString( PyExc_ValueError, strings::orderAlreadyExist );

    py::throw_error_already_set();
}


} /* namespace pyxchange */



/* EOF */

