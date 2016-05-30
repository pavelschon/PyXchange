/**
 * @brief This module implements simulator of exchange
 * @file OrderBook.cpp
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
void OrderBook::cancelOrder( const MatcherPtr& matcher, const TraderPtr& trader, const py::dict& decoded )
{
    const orderId_t orderId = py::extract<const orderId_t>( decoded[ keys::orderId ] );

    size_t n = 0;

    // we don't know if order is buy or sell, so we cancel it in both containers
    n += cancelOrder<BidOrderContainer>( bidOrders, matcher, trader, orderId );
    n += cancelOrder<AskOrderContainer>( askOrders, matcher, trader, orderId );

    if( n > 0 )
    {
        trader->notifyCancelOrderSuccess( orderId );
    }
    else
    {
        trader->notifyCancelOrderError( orderId, strings::orderDoesNotExist );

        PyErr_SetString( PyExc_ValueError, strings::orderDoesNotExist.c_str() );

        py::throw_error_already_set();
    }
}


/**
 * @brief FIXME
 *
 */
template<typename OrderContainer>
size_t OrderBook::cancelOrder( typename OrderContainer::type& orders, const MatcherConstPtr& matcher,
                               const TraderPtr& trader, const orderId_t orderId )
{
          auto& idx = orders.template get<tags::idxTraderOrderId>();
    const auto& key = std::make_tuple( trader, orderId );
    const auto  it  = idx.find( key );

    if( it != idx.end() )
    {
        const auto order = *it; // no reference here!

        idx.erase( it );

        aggregatePriceLevel<OrderContainer>( orders, matcher, order->price, order->side );

        return 1;
    }
    else
    {
        return 0;
    }
}


} /* namespace pyxchange */



/* EOF */

