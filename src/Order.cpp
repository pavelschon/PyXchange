/**
 * @brief This module implements simulator of exchange
 * @file Order.cpp
 *
 */


#include "Order.hpp"
#include "Utils.hpp"


namespace pyxchange
{

namespace py = boost::python;


/**
 * @brief Constructor
 *
 */
Order::Order( const TraderPtr& trader_, const boost::python::dict& decoded ):

      trader( trader_ )
    , side( decoded[ keys::side ] )
    , time( std::chrono::high_resolution_clock::now() )
    , orderId( py::extract<const orderId_t>( decoded[ keys::orderId ] ) )
    , price( py::extract<const price_t>( decoded[ keys::price ] ) )
    , quantity( py::extract<const quantity_t>( decoded[ keys::quantity ] ) )
{
    if( side != side::bid && side != side::ask )
    {
        PyErr_SetString( PyExc_ValueError, strings::unknownSide );

        py::throw_error_already_set();
    }
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


/**
 * @brief FIXME
 *
 */
orderId_t Order::getId( void ) const
{
    return orderId;
}


} /* namespace pyxchange */



/* EOF */

