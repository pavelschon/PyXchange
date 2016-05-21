/**
 * @brief This module implements simulator of exchange
 * @file Order.cpp
 *
 */


#include "Order.hpp"


namespace pyxchange
{

namespace py = boost::python;


/**
 * @brief Constructor
 *
 */
Order::Order( const TraderPtr& trader_, const boost::python::dict& decoded ):

      trader( trader_ )
    , side( decoded["side"] )
    , price( py::extract<const price_t>( decoded["price"] ) )
    , quantity( py::extract<const quantity_t>( decoded["quantity"] ) )
    , orderId( py::extract<const orderId_t>( decoded["orderId"] ) )
{

}


/**
 * @brief FIXME
 *
 */
price_t Order::getPrice( void ) const
{
    return price;
}


/**
 * @brief FIXME
 *
 */
time_t Order::getTime( void ) const
{
    return time;
}


} /* namespace pyxchange */



/* EOF */


