/**
 * @brief This module implements simulator of exchange
 * @file OrderBook.cpp
 *
 */


#include "OrderBook.hpp"
#include "../Message.hpp"


namespace pyxchange
{

namespace py = boost::python;


/**
 * @brief FIXME
 *
 */
void OrderBook::createOrder( const TraderPtr& trader, const boost::python::dict& decoded )
{
    const py::str order_side( decoded["side"] );
    const py::long_ price( decoded[ "price" ] );
    const py::long_ quantity( decoded[ "quantity" ] );
    const py::long_ orderId( decoded[ "orderId" ] );

    const Order order( trader, order_side, price, quantity, orderId );

    if( order_side == side::bid )
    {
        createOrder( bidOrders, trader, order );
    }
    else if( order_side == side::ask )
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

