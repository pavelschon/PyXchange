/**
 * @brief This module implements simulator of exchange
 * @file Order.cpp
 *
 */


#include "order/Order.hpp"
#include "utils/Exception.hpp"
#include "utils/Constants.hpp"
#include "utils/Side.hpp"


namespace pyxchange
{

namespace py = boost::python;


/**
 * @brief Constructor
 *
 */
Order::Order( const TraderPtr& trader_, const py::dict& decoded ):
      trader{ trader_ }
    , time{ std::chrono::high_resolution_clock::now() }
    , side{ extractSide( decoded ) }
    , orderId{ extractOrderId( decoded ) }
    , price{ extractPrice( decoded ) }
    , quantity{ extractQuantity( decoded ) }
{

}


/**
 * @brief FIXME
 *
 */
std::string Order::toString( void ) const
{
    return ( boost::format( format::f4::order ) % orderId
        % side::toBidAsk( side ) % quantity % price ).str();
}


/**
 * @brief FIXME
 *
 */
side_t Order::extractSide( const py::dict& decoded )
{
    const auto exceptions{ PyExc_KeyError, PyExc_TypeError };

    const auto decode = [ &decoded ]() {
        const std::wstring side_ = py::extract<const std::wstring>( decoded[ keys::side ] );

        if( side_ == side::wBuy )
        {
            return side::bid_;
        }
        else if( side_ == side::wSell )
        {
            return side::ask_;
        }
        else
        {
            throw side::WrongSide();
        }
    };

    return pyexc::translate<side::WrongSide>( decode, exceptions );
}


/**
 * @brief FIXME
 *
 */
orderId_t Order::extractOrderId( const py::dict& decoded )
{
    const auto exceptions{ PyExc_KeyError, PyExc_TypeError };

    const auto decode = [ &decoded ]() {
        const orderId_t orderId_ = py::extract<const orderId_t>( decoded[ keys::orderId ] );

        if( orderId_ > 0 )
        {
            return orderId_;
        }
        else
        {
            throw pyexc::OrderIdError();
        }
    };

    return pyexc::translate<pyexc::OrderIdError>( decode, exceptions );
}


/**
 * @brief FIXME
 *
 */
price_t Order::extractPrice( const py::dict& decoded )
{
    const auto exceptions{ PyExc_KeyError, PyExc_TypeError };

    const auto decode = [ &decoded ]() {
        const price_t price_ = py::extract<const price_t>( decoded[ keys::price ] );

        if( price_ > 0 )
        {
            return price_;
        }
        else
        {
            throw pyexc::PriceError();
        }
    };

    return pyexc::translate<pyexc::PriceError>( decode, exceptions );
}


/**
 * @brief FIXME
 *
 */
quantity_t Order::extractQuantity( const py::dict& decoded )
{
    const auto exceptions{ PyExc_KeyError, PyExc_TypeError };

    const auto decode = [ &decoded ]() {
        const quantity_t quantity_ = py::extract<const quantity_t>( decoded[ keys::quantity ] );

        if( quantity_ > 0 )
        {
            return quantity_;
        }
        else
        {
            throw pyexc::QuantityError();
        }
    };

    return pyexc::translate<pyexc::QuantityError>( decode, exceptions );
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
TraderPtr Order::getTrader( void ) const
{
    return trader.lock();
}


/**
 * @brief FIXME
 *
 */
TraderOrderId Order::getUnique( void ) const
{
    return std::make_tuple( trader.lock(), orderId );
}


} /* namespace pyxchange */



/* EOF */

