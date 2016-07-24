/**
 * @brief   Implementation of orderbook, aggregate price levels
 * @file    OrderBookAggr.cpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */


#include "orderbook/OrderBook.hpp"
#include "client/Client.hpp"
#include "utils/Constants.hpp"
#include "utils/Side.hpp"


namespace pyxchange
{

namespace py = boost::python;


/**
 * @brief Aggregate set of price levels in given orders container, notify clients
 * @param orders OrdersContainer (bid or ask)
 * @param priceLevels set
 * @param side of orders
 *
 */
template<typename OrderContainer>
void OrderBook::aggregateSetPriceLevels( const OrderContainer& orders,
                                         const typename OrderContainer::price_set& priceLevels,
                                         const side_t side_ ) const
{
    for( const auto price : priceLevels )
    {
        aggregatePriceLevel( orders, price, side_ );
    }
}


/**
 * @brief Aggregate single price level in given orders container, notify clients
 * @param orders OrdersContainer (bid or ask)
 * @param priceLevel
 * @param side of orders
 *
 */
template<typename OrderContainer>
inline void OrderBook::aggregatePriceLevel( const OrderContainer& orders, const price_t priceLevel, const side_t side_ ) const
{
    const auto& idx = orders.container.template get<tags::idxPrice>();
    const auto  end = idx.upper_bound( priceLevel );
          auto  it  = idx.lower_bound( priceLevel );

    quantity_t quantity = 0;

    for(; it != end; ++it )
    {
        const auto& order = *it;

        quantity += order->quantity;
    }

    Client::notifyOrderBook( clients, priceLevel, side_, quantity );
}


template void OrderBook::aggregateSetPriceLevels<BidOrderContainer>(
    const BidOrderContainer& orders,
    const BidOrderContainer::price_set& priceLevels,
    const side_t side_ ) const;

template void OrderBook::aggregateSetPriceLevels<AskOrderContainer>(
    const AskOrderContainer& orders,
    const AskOrderContainer::price_set& priceLevels,
    const side_t side_ ) const;

template void OrderBook::aggregatePriceLevel<BidOrderContainer>(
    const BidOrderContainer& orders,
    const price_t priceLevel, const side_t side_ ) const;

template void OrderBook::aggregatePriceLevel<AskOrderContainer>(
    const AskOrderContainer& orders,
    const price_t priceLevel, const side_t side_ ) const;


} /* namespace pyxchange */



/* EOF */

