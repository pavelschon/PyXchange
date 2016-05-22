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
    , side( decoded["side"] )
    , time( std::chrono::high_resolution_clock::now() )
    , orderId( py::extract<const orderId_t>( decoded["orderId"] ) )
    , price( py::extract<const price_t>( decoded["price"] ) )
    , quantity( py::extract<const quantity_t>( decoded["quantity"] ) )
{
    if( side == side::bid )
    {

    }
    else if( side == side::ask )
    {

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
bool Order::CompareByID::operator()( const OrderConstPtr& lhs, const OrderConstPtr& rhs ) const
{
    return lhs->orderId < rhs->orderId;
}


} /* namespace pyxchange */



/* EOF */


