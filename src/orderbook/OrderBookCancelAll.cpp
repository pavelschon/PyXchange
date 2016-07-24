/**
 * @brief   Implementation of orderbook, message cancelAll
 * @file    OrderBookCancelAll.cpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */


#include "orderbook/OrderBook.hpp"
#include "order_container/OrderContainer.hpp"
#include "client/Trader.hpp"
#include "utils/Constants.hpp"
#include "utils/Side.hpp"


namespace pyxchange
{


/**
 * @brief Cancel all orders of given trader
 * @param trader canceling orders
 *
 */
void OrderBook::cancelAllOrders( const TraderPtr& trader )
{
    const size_t numBid = cancelAllOrders( bidOrders, trader, side::bid_ );
    const size_t numAsk = cancelAllOrders( askOrders, trader, side::ask_ );

    if( numBid || numAsk )
    {
        logger.debug( format::f3::logTraderCanceledAll, trader->toString(), numBid, numAsk );
    }
}


/**
 * @brief Cancel all orders of given trader
 * @param orders OrdersContainer (bid or ask)
 * @param trader canceling orders
 * @param side of orders
 *
 */
template<typename OrderContainer>
size_t OrderBook::cancelAllOrders( OrderContainer& orders, const TraderPtr& trader, const side_t side_ )
{
    typename OrderContainer::element_type::price_set priceLevels;

          auto &idx = orders->container.template get<tags::idxTrader>();
          auto it   = idx.lower_bound( trader );
    const auto end  = idx.upper_bound( trader );

    size_t n = 0;

    while( it != end )
    {
        const auto& order = *it;

        priceLevels.insert( order->price );

        idx.erase( it++ );

        ++n;
    }

    aggregateSetPriceLevels( orders, priceLevels, side_ );

    return n;
}


} /* namespace pyxchange */



/* EOF */

