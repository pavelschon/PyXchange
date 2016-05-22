/**
 * @brief This module implements simulator of exchange
 * @file CreateOrder.cpp
 *
 */


#include "orderbook/OrderBook.hpp"
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
    const Order order( trader, decoded );

    if( order.side == side::bid )
    {
        createOrder( bidOrders, trader, order );
    }
    else if( order.side == side::ask )
    {
        createOrder( askOrders, trader, order );
    }
    else
    {
        PyErr_SetString( PyExc_KeyError, "unknown side" );

        py::throw_error_already_set();
    }
}


/**
 * @brief FIXME
 *
 */
template<typename T>
void OrderBook::createOrder( T& orders, const TraderPtr& trader, const Order& order )
{

}


} /* namespace pyxchange */



/* EOF */

