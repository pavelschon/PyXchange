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
        createOrder( bidOrders, trader, result.first );
    }
    else if( result.first->side == side::ask )
    {
        createOrder( askOrders, trader, result.first );
    }
}


/**
 * @brief FIXME
 *
 */
template<typename T>
void OrderBook::createOrder( T& orders, const TraderPtr& trader, const OrderPtr& order )
{

}


} /* namespace pyxchange */



/* EOF */

