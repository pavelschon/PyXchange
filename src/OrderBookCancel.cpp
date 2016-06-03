/**
 * @brief This module implements simulator of exchange
 * @file OrderBook.cpp
 *
 */


#include "OrderBook.hpp"
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
    const orderId_t orderId = py::extract<const orderId_t>( decoded[ keys::orderId ] );

    size_t n = 0;

    // we don't know if order is buy or sell, so we cancel it in both containers
    n += cancelOrder<BidOrderContainer>( bidOrders, trader, orderId );
    n += cancelOrder<AskOrderContainer>( askOrders, trader, orderId );

    if( ! n )
    {
        logger.warning( boost::format( format::f2::logOrderDoesNotExist ) % trader->getName() % orderId );

        trader->notifyOrderDoesNotExist( orderId );
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
        const auto order    = *it; // no reference here!

        idx.erase( it );

        trader->notifyCancelOrderSuccess( order->orderId );

        logger.info( boost::format( format::f3::traderCanceledOne ) % trader->getName()
                     % side::toBidAsk( order->side ) % order->orderId );

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

