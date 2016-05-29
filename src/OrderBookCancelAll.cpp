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
size_t OrderBook::cancelAllOrders( const MatcherConstPtr& matcher, const TraderPtr& trader )
{
    size_t n = 0;

    // we don't know if order is buy or sell, so we cancel it in both containers
    n += cancelAllOrders<BidOrderContainer>( bidOrders, matcher, trader, side::bid_ );
    n += cancelAllOrders<AskOrderContainer>( askOrders, matcher, trader, side::ask_ );

    return n;
}


/**
 * @brief FIXME
 *
 */
template<typename OrderContainer>
size_t OrderBook::cancelAllOrders( typename OrderContainer::type& orders, const MatcherConstPtr& matcher,
                                   const TraderPtr& trader, const side_t side_ )
{
    typename OrderContainer::price_set priceLevels;

    auto &idx      = orders.template get<tags::idxTrader>();
    auto it        = idx.lower_bound( trader );
    const auto end = idx.upper_bound( trader );

    size_t n = 0;

    while( it != end )
    {
        const auto& order = *it;

        priceLevels.insert( order->price );

        idx.erase( it++ );

        ++n;
    }

    for( const auto price : priceLevels )
    {
        aggregatePriceLevel<OrderContainer>( orders, matcher, price, side_ );
    }

    return n;
}


template size_t OrderBook::cancelAllOrders<BidOrderContainer>(
    BidOrderContainer::type& orders, const MatcherConstPtr& matcher,
    const TraderPtr& trader, const side_t side_ );


template size_t OrderBook::cancelAllOrders<AskOrderContainer>(
    AskOrderContainer::type& orders, const MatcherConstPtr& matcher,
    const TraderPtr& trader, const side_t side_ );


} /* namespace pyxchange */



/* EOF */

