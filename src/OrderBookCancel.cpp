/**
 * @brief This module implements simulator of exchange
 * @file OrderBook.cpp
 *
 */


#include "OrderBook.hpp"
#include "Matcher.hpp"
#include "Trader.hpp"


namespace pyxchange
{


namespace py = boost::python;


namespace format
{

const boost::format traderCanceledOne( "%|| cancelled %|| order id %||" );
const boost::format logOrderDoesNotExist( "%|| canceling order id %||, but it does not exists" );

} /* namespace message */


/**
 * @brief FIXME
 *
 */
void OrderBook::cancelOrder( const MatcherConstPtr& matcher, const TraderPtr& trader, const py::dict& decoded )
{
    const orderId_t orderId = py::extract<const orderId_t>( decoded[ keys::orderId ] );

    size_t n = 0;

    // we don't know if order is buy or sell, so we cancel it in both containers
    n += cancelOrder<BidOrderContainer>( bidOrders, matcher, trader, orderId );
    n += cancelOrder<AskOrderContainer>( askOrders, matcher, trader, orderId );

    if( ! n )
    {
        matcher->log( log::warning, boost::format( format::logOrderDoesNotExist )
                      % trader->getName() % orderId );

        trader->notifyOrderDoesNotExist( orderId );

        trader->disconnect();
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
        const auto order    = *it; // no reference here!

        idx.erase( it );

        trader->notifyCancelOrderSuccess( order->orderId );

        matcher->log( log::info, boost::format( format::traderCanceledOne ) % trader->getName()
                      % side::toBidAsk( order->side ) % order->orderId );

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

