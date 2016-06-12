/**
 * @brief   FIXME
 * @file    Order.cpp
 *
 */


#include "order/Order.hpp"
#include "client/Trader.hpp"
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
Order::Order( const TraderPtr& trader_, const py::dict& decoded, const bool isMarketOrder_ ):
      isMarketOrder{ isMarketOrder_ }
    , trader{ trader_ }
    , time{ std::chrono::high_resolution_clock::now() }
    , side{ extractSide( decoded ) }
    , orderId{ isMarketOrder ? 0 : extractOrderId( decoded ) }
    , price{ extractPrice( isMarketOrder, side, decoded ) }
    , quantity{ extractQuantity( decoded ) }
{

}


/**
 * @brief FIXME
 *
 */
std::string Order::toString( void ) const
{
    const TraderPtr& trader_ = trader.lock();

    if( isMarketOrder )
    {
        return ( boost::format( format::f2::marketOrder )
                 % side::toBidAsk( side ) % quantity ).str();
    }
    else
    {
        return ( boost::format( format::f3::order )
                 % side::toBidAsk( side ) % quantity % price ).str();
    }
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
price_t Order::extractPrice( const bool isMarketOrder_, const side_t side_, const py::dict& decoded )
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

    if( isMarketOrder_ && side::isBid( side_ ) )
    {
        return std::numeric_limits<const price_t>::max();
    }
    else if( isMarketOrder_ && side::isAsk( side_ ) )
    {
        return std::numeric_limits<const price_t>::min();
    }
    else
    {
        return pyexc::translate<pyexc::PriceError>( decode, exceptions );
    }
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
    if( side::isBid( side ) && side::isAsk( order->side ) )
    {
        return price >= order->price;
    }
    else if( side::isAsk( side ) && side::isBid( order->side ) )
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

