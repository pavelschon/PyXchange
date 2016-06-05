/**
 * @brief This module implements simulator of exchange
 * @file OrderBookSelfMatch.cpp
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
template<typename OrderContainer>
bool OrderBook::handleSelfMatch( const typename OrderContainer::type& orders,
                                 const TraderPtr& trader, const OrderConstPtr& order ) const
{
    Order order_ = *order; // copy of order
    auto &idx    = orders.template get<tags::idxPriceTime>();
    auto it      = idx.begin();

    while( it != idx.end() && order_.comparePrice( *it ) && order_.quantity > 0 )
    {
        const auto& oppOrder = *it;

        if( trader == oppOrder->getTrader() )
        {
            trader->notifyError( format::f0::selfMatch.str() );

            logger.info( boost::format( format::f3::logSelfMatch ) % trader->toString()
                         % order->toString() % oppOrder->toString() );

            return false;
        }

        order_.quantity -= std::min( order_.quantity, oppOrder->quantity );
    }

    return true;
}


template bool OrderBook::handleSelfMatch<BidOrderContainer>(
    const BidOrderContainer::type& orders, const TraderPtr& trader, const OrderConstPtr& order ) const;

template bool OrderBook::handleSelfMatch<AskOrderContainer>(
    const AskOrderContainer::type& orders, const TraderPtr& trader, const OrderConstPtr& order ) const;


} /* namespace pyxchange */



/* EOF */

