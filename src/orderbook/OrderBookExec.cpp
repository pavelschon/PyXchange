/**
 * @brief   Implementation of orderbook, order execution, match event
 * @file    OrderBookExec.cpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */


#include "orderbook/OrderBook.hpp"
#include "order_container/OrderContainer.hpp"
#include "client/Trader.hpp"
#include "client/Client.hpp"
#include "utils/Constants.hpp"
#include "utils/Side.hpp"


namespace pyxchange
{


/**
 * @brief Handle order execution agains orders in given container, notify clients
 * @param orders OrdersContainer (bid or ask)
 * @param order newly created
 *
 */
template<typename OrderContainer>
void OrderBook::handleExecution( OrderContainer& orders, const OrderPtr& order )
{
    typename OrderContainer::element_type::price_set priceLevels;

    auto &idx = orders->container.template get<tags::idxPriceTime>();
    auto it   = idx.begin();

    quantity_t totalMatchQuantity = 0;

    while( it != idx.end() && order->comparePrice( *it ) && order->quantity > 0 )
    {
        const auto oppOrder = *it;
        const price_t  matchPrice  = oppOrder->price;
        const quantity_t matchQty  = std::min( order->quantity, oppOrder->quantity );

        order->quantity    -= matchQty;
        oppOrder->quantity -= matchQty;
        totalMatchQuantity += matchQty;

        priceLevels.insert( matchPrice );

        if( oppOrder->quantity < 1 )
        {
            idx.erase( it++ );
        }
        else
        {
            ++it;
        }

        notifyExecution( order, oppOrder, matchQty );
    }

    if( totalMatchQuantity > 0 )
    {
        aggregateSetPriceLevels( orders, priceLevels, side::opposite( order->side ) );
    }
}


template void OrderBook::handleExecution( BidOrderContainerPtr& orders, const OrderPtr& order );
template void OrderBook::handleExecution( AskOrderContainerPtr& orders, const OrderPtr& order );


/**
 * @brief Notify client and traders about match event
 * @param order which as matched
 * @param oppOrder opposite order which has matched
 * @param matchQty matched quantity
 *
 */
void OrderBook::notifyExecution( const OrderConstPtr& order, const OrderConstPtr& oppOrder,
                                 const quantity_t matchQty ) const
{
    const TraderPtr& trader    = order->getTrader();
    const TraderPtr& oppTrader = oppOrder->getTrader();
    const price_t matchPrice   = oppOrder->price;

    logger.debug( format::f2::logExecution, matchQty, matchPrice );

    if( trader ) // it's created from weak_ptr, so we must check for nullptr
    {
        trader->notifyTrade( order->orderId, matchPrice, matchQty );
    }

    if( oppTrader ) // it's created from weak_ptr, so we must check for nullptr
    {
        oppTrader->notifyTrade( oppOrder->orderId, matchPrice, matchQty );
    }

    Client::notifyTrade( clients, order->time, matchPrice, matchQty );
}


} /* namespace pyxchange */



/* EOF */

