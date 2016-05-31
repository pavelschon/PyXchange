/**
 * @brief This module implements simulator of exchange
 * @file OrderBookInsert.cpp
 *
 */


#include "OrderBook.hpp"
#include "Matcher.hpp"
#include "Trader.hpp"
#include "Utils.hpp"


namespace pyxchange
{

namespace py = boost::python;


/**
 * @brief FIXME
 *
 */
template<typename OrderContainer, typename OppOrderContainer>
void OrderBook::insertOrder( typename OrderContainer::type& orders, typename OppOrderContainer::type& oppOrders,
                             const MatcherConstPtr& matcher, const TraderPtr& trader, const OrderPtr& order )
{
    const auto& result = orders.template insert( order );

    if( result.second )
    {
        handleSelfMatch<OppOrderContainer>( oppOrders, matcher, trader, order );
        handleExecution<OppOrderContainer>( oppOrders, matcher, trader, order );

        if( order->quantity > 0 )
        {
            trader->notifyCreateOrderSuccess( order->orderId );

            aggregatePriceLevel<OrderContainer>( orders, matcher, order->price, order->side );

            matcher->log( log::info, boost::format( format::traderAddedOrder ) % trader->getName()
                          % side::toBuySell( order->side ) % order->orderId % order->price % order->quantity );
        }
        else
        {
            // order has no resting quantity (was executed), so remove it
            orders.template erase( result.first );
        }
    }
    else
    {
        trader->notifyCreateOrderError( order->orderId, strings::orderAlreadyExist );

        PyErr_SetString( PyExc_ValueError, strings::orderAlreadyExist.c_str() );

        py::throw_error_already_set();
    }
}


template void OrderBook::insertOrder<BidOrderContainer, AskOrderContainer>(
    BidOrderContainer::type& orders, AskOrderContainer::type& oppOrders,
    const MatcherConstPtr& matcher, const TraderPtr& trader, const OrderPtr& order );

template void OrderBook::insertOrder<AskOrderContainer, BidOrderContainer>(
    AskOrderContainer::type& orders, BidOrderContainer::type& oppOrders,
    const MatcherConstPtr& matcher, const TraderPtr& trader, const OrderPtr& order );


} /* namespace pyxchange */



/* EOF */

