/**
 * @brief   Implementation of orderbook, insert order
 * @file    OrderBookInsert.cpp
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
void OrderBook::insertOrder( typename OrderContainer::type& orders,
                             typename OppOrderContainer::type& oppOrders,
                             const TraderPtr& trader, const OrderPtr& order )
{
    const auto& result = orders.template insert( order );

    if( result.second )
    {
        handleExecution<OppOrderContainer>( oppOrders, order );

        if( order->quantity > 0 )
        {
            trader->notifyCreateOrderSuccess( order->orderId, order->quantity );

            aggregatePriceLevel<OrderContainer>( orders, order->price, order->side );

            logger.info( boost::format( format::f2::logTraderAddedOrder )
                         % trader->toString() % order->toString() );
        }
        else
        {
            // order has no resting quantity (was executed), so remove it
            orders.template erase( result.first );
        }
    }
    else
    {
        logger.warning( boost::format( format::f2::logOrderAlreadyExist )
                        % trader->toString() % order->toString() );

        trader->notifyError( format::f0::orderAlreadyExist.str() );
    }
}


template void OrderBook::insertOrder<BidOrderContainer, AskOrderContainer>(
    BidOrderContainer::type& orders, AskOrderContainer::type& oppOrders,
    const TraderPtr& trader, const OrderPtr& order );

template void OrderBook::insertOrder<AskOrderContainer, BidOrderContainer>(
    AskOrderContainer::type& orders, BidOrderContainer::type& oppOrders,
    const TraderPtr& trader, const OrderPtr& order );


} /* namespace pyxchange */



/* EOF */

