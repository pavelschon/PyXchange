/**
 * @brief This module implements simulator of exchange
 * @file OrderBook.cpp
 *
 */


#include "OrderBook.hpp"
#include "Exception.hpp"
#include "Constants.hpp"
#include "Trader.hpp"
#include "Side.hpp"


namespace pyxchange
{


namespace py = boost::python;


/**
 * @brief FIXME
 *
 */
void OrderBook::cancelOrder( const TraderPtr& trader, const py::dict& decoded )
{
    try
    {
        const orderId_t orderId = Order::extractOrderId( decoded );

        size_t n = 0;

        // we don't know if order is buy or sell, so we cancel it in both containers
        n += cancelOrder<BidOrderContainer>( bidOrders, trader, orderId );
        n += cancelOrder<AskOrderContainer>( askOrders, trader, orderId );

        if( ! n )
        {
            logger.warning( boost::format( format::f2::logOrderDoesNotExist ) % trader->toString() % orderId );

            trader->notifyError( format::f0::orderDoesNotExist.str() );
        }
    }
    catch( const pyexc::OrderIdError& )
    {
        logger.warning( boost::format( format::f1::logWrongOrderId ) % trader->toString() );

        trader->notifyError( format::f0::wrongOrderId.str() );
    }
}


/**
 * @brief FIXME
 *
 */
template<typename OrderContainer>
size_t OrderBook::cancelOrder( typename OrderContainer::type& orders, const TraderPtr& trader, const orderId_t orderId )
{
          auto& idx = orders.template get<tags::idxTraderOrderId>();
    const auto& key = std::make_tuple( trader, orderId );
    const auto  it  = idx.find( key );

    if( it != idx.end() )
    {
        const auto order = *it;

        idx.erase( it );

        trader->notifyCancelOrderSuccess( order->orderId, order->quantity );

        logger.info( boost::format( format::f2::logTraderCanceledOne ) % trader->toString() % order->toString() );

        aggregatePriceLevel<OrderContainer>( orders, order->price, order->side );

        return 1;
    }
    else
    {
        return 0;
    }
}


} /* namespace pyxchange */



/* EOF */

