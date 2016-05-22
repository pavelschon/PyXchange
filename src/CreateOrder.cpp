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
        PyErr_SetString( PyExc_ValueError, "order already inserted" );

        py::throw_error_already_set();
    }
    else if( result.first->side == side::bid )
    {
        bidOrders.insert( result.first );
    }
    else if( result.first->side == side::ask )
    {
        askOrders.insert( result.first );
    }

    py::dict response;

    response["message"] = message::executionReport;
    response["report" ] = report::new_;
    response["orderId"] = result.first->orderId;

    // send response
    trader->writeData( response );
}


/**
 * @brief FIXME
 *
 */
// template<typename T>
// void OrderBook::createOrder( T& orders, const TraderPtr& trader, const OrderPtr& order )
// {
//
// }


} /* namespace pyxchange */



/* EOF */

