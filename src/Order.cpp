/**
 * @brief This module implements simulator of exchange
 * @file Order.cpp
 *
 */


#include "Order.hpp"
#include "Trader.hpp"
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
    , side( extractSide( trader_, decoded ) )
    , time( std::chrono::high_resolution_clock::now() )
    , orderId( py::extract<const orderId_t>( decoded[ keys::orderId ] ) )
    , price( py::extract<const price_t>( decoded[ keys::price ] ) )
    , quantity( py::extract<const quantity_t>( decoded[ keys::quantity ] ) )
{

}


/**
 * @brief FIXME
 *
 */
side_t Order::extractSide( const TraderPtr& trader, const boost::python::dict& decoded )
{
    const auto& side_ = decoded[ keys::side ];

    if( side_ == side::buy )
    {
        return side::bid_;
    }
    else if( side_ == side::sell )
    {
        return side::ask_;
    }
    else
    {
        trader->notifyError( strings::unknownSide );

        PyErr_SetString( PyExc_ValueError, strings::unknownSide.c_str() );

        py::throw_error_already_set();
        throw; // suppress warning
    }
}


/**
 * @brief FIXME
 *
 */
bool Order::isBid( void ) const
{
    return side == side::bid_;
}


/**
 * @brief FIXME
 *
 */
bool Order::isAsk( void ) const
{
    return side == side::ask_;
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


/**
 * @brief FIXME
 *
 */
bool Order::comparePrice( const OrderConstPtr& order ) const
{
    if( isBid() && order->isAsk() )
    {
        return price >= order->price;
    }
    else if( isAsk() && order->isBid() )
    {
        return price <= order->price;
    }
    else
    {
        return false;
    }
}


} /* namespace pyxchange */



/* EOF */

