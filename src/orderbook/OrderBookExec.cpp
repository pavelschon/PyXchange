/**
 * @brief This module implements simulator of exchange
 * @file OrderBook.cpp
 *
 */


#include "orderbook/OrderBook.hpp"
#include "client/Trader.hpp"
#include "client/Client.hpp"
#include "Constants.hpp"
#include "Side.hpp"


namespace pyxchange
{

namespace py = boost::python;


/**
 * @brief FIXME
 *
 */
template<typename OrderContainer>
void OrderBook::handleExecution( typename OrderContainer::type& orders,
                                 const TraderPtr& trader, const OrderPtr& order )
{
    typename OrderContainer::price_set priceLevels;

    auto &idx = orders.template get<tags::idxPriceTime>();
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

        notifyExecution( trader, order, oppOrder, matchQty );
    }

    if( totalMatchQuantity > 0 )
    {
        aggregateSetPriceLevels<OrderContainer>( orders, priceLevels, side::opposite( order->side ) );
    }
}


template void OrderBook::handleExecution<BidOrderContainer>(
    BidOrderContainer::type& orders, const TraderPtr& trader, const OrderPtr& order );

template void OrderBook::handleExecution<AskOrderContainer>(
    AskOrderContainer::type& orders, const TraderPtr& trader, const OrderPtr& order );


/**
 * @brief FIXME
 *
 */
void OrderBook::notifyExecution( const TraderPtr& trader, const OrderPtr& order,
                                 const OrderPtr& oppOrder, const quantity_t matchQty ) const
{
    const price_t matchPrice   = oppOrder->price;
    const TraderPtr& oppTrader = oppOrder->getTrader();

    logger.info( boost::format( format::f2::logExecution ) % matchQty % matchPrice );

    trader->notifyTrade( order->orderId, matchPrice, matchQty );

    if( oppTrader ) // it's created from weak_ptr, so we muust check for nullptr
    {
        oppTrader->notifyTrade( oppOrder->orderId, matchPrice, matchQty );
    }

    Client::notifyTrade( clients, order->time, matchPrice, matchQty );
}


} /* namespace pyxchange */



/* EOF */

