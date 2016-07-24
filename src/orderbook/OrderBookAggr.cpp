/**
 * @brief   Implementation of orderbook, aggregate price levels
 * @file    OrderBookAggr.cpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */


#include "orderbook/OrderBook.hpp"
#include "order/OrderContainer.hpp"
#include "client/Client.hpp"
#include "utils/Constants.hpp"
#include "utils/Side.hpp"


namespace pyxchange
{


/**
 * @brief Aggregate set of price levels in given orders container, notify clients
 * @param orders OrdersContainer (bid or ask)
 * @param priceLevels set
 * @param side of orders
 *
 */
template<typename OrderContainer>
void OrderBook::aggregateSetPriceLevels( const OrderContainer& orders,
                                         const typename OrderContainer::element_type::price_set& priceLevels,
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
void OrderBook::aggregatePriceLevel( const OrderContainer& orders, const price_t priceLevel, const side_t side_ ) const
{
    const auto& idx = orders->container.template get<tags::idxPrice>();
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


template void OrderBook::aggregateSetPriceLevels( const BidOrderContainerPtr& orders,
    const BidOrderContainerPtr::element_type::price_set& priceLevels, const side_t side_ ) const;

template void OrderBook::aggregateSetPriceLevels( const AskOrderContainerPtr& orders,
    const AskOrderContainerPtr::element_type::price_set& priceLevels, const side_t side_ ) const;

template void OrderBook::aggregatePriceLevel( const BidOrderContainerPtr& orders,
    const price_t priceLevel, const side_t side_ ) const;

template void OrderBook::aggregatePriceLevel( const AskOrderContainerPtr& orders,
    const price_t priceLevel, const side_t side_ ) const;


} /* namespace pyxchange */



/* EOF */

