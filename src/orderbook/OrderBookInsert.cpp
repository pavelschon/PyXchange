/**
 * @brief   Implementation of orderbook, insert order
 * @file    OrderBookInsert.cpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */


#include "orderbook/OrderBook.hpp"
#include "client/Trader.hpp"
#include "utils/Constants.hpp"
#include "utils/Side.hpp"


namespace pyxchange
{

namespace py = boost::python;


/**
 * @brief Insert order into give OrderContainer, forward processing into handleExecution
 * @param orders OrdersContainer (bid or ask)
 * @param oppOrders OrdersContainer (bid or ask), opposite to orders
 * @param trader inserting order
 * @param order to be inserted
 *
 */
template<typename OrderContainer, typename OppOrderContainer>
void OrderBook::insertOrder( OrderContainer& orders, OppOrderContainer& oppOrders,
                             const TraderPtr& trader, const OrderPtr& order )
{
    const auto& result = orders.container.insert( order );

    if( result.second )
    {
        handleExecution( oppOrders, order );

        if( order->quantity > 0 )
        {
            trader->notifyCreateOrderSuccess( order->orderId, order->quantity );

            aggregatePriceLevel( orders, order->price, order->side );

            logger.debug( format::f2::logTraderAddedOrder, trader->toString(), order->toString() );
        }
        else
        {
            // order has no resting quantity (was executed), so remove it
            orders.template container.erase( result.first );
        }
    }
    else
    {
        logger.debug( format::f2::logOrderAlreadyExist, trader->toString(), order->orderId );

        trader->notifyError( format::f0::orderAlreadyExist.str() );
    }
}


template void OrderBook::insertOrder<BidOrderContainer, AskOrderContainer>(
    BidOrderContainer& orders, AskOrderContainer& oppOrders, const TraderPtr& trader, const OrderPtr& order );

template void OrderBook::insertOrder<AskOrderContainer, BidOrderContainer>(
    AskOrderContainer& orders, BidOrderContainer& oppOrders, const TraderPtr& trader, const OrderPtr& order );


} /* namespace pyxchange */



/* EOF */

