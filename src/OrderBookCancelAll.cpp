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
void OrderBook::cancelAllOrders( const TraderPtr& trader )
{
    const size_t numBid = cancelAllOrders<BidOrderContainer>( bidOrders, trader, side::bid_ );
    const size_t numAsk = cancelAllOrders<AskOrderContainer>( askOrders, trader, side::ask_ );

    if( numBid || numAsk )
    {
        logger.info( boost::format( format::f3::traderCanceledAll ) % trader->getName() % numBid % numAsk );
    }
}


/**
 * @brief FIXME
 *
 */
template<typename OrderContainer>
size_t OrderBook::cancelAllOrders( typename OrderContainer::type& orders, const TraderPtr& trader, const side_t side_ )
{
    typename OrderContainer::price_set priceLevels;

          auto &idx = orders.template get<tags::idxTrader>();
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

    aggregateAllPriceLevels<OrderContainer>( orders, priceLevels, side_ );

    return n;
}


} /* namespace pyxchange */



/* EOF */

