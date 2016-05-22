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
    , time( std::chrono::high_resolution_clock::now() )
    , orderId( py::extract<const orderId_t>( decoded["orderId"] ) )
    , price( py::extract<const price_t>( decoded["price"] ) )
    , quantity( py::extract<const quantity_t>( decoded["quantity"] ) )
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
prio_t Order::getTime( void ) const
{
    return time;
}


} /* namespace pyxchange */



/* EOF */


