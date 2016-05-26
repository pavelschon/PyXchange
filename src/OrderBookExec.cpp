/**
 * @brief This module implements simulator of exchange
 * @file CancelOrder.cpp
 *
 */


#include "OrderBook.hpp"
#include "Client.hpp"
#include "Trader.hpp"
#include "Utils.hpp"

#include <iostream>


namespace pyxchange
{

namespace py = boost::python;



/**
 * @brief FIXME
 *
 */
template<typename OrderContainer>
void OrderBook::handleExecution( typename OrderContainer::type& orders, const MatcherConstPtr& matcher, const TraderPtr& trader, const OrderPtr& order )
{
    typename OrderContainer::price_set priceLevels;
    typename OrderContainer::type::template index<tags::idxPriceTime>::type  const &idx        = orders.template get<tags::idxPriceTime>();
    typename OrderContainer::type::template index<tags::idxPriceTime>::type::const_iterator it = idx.begin();

    quantity_t totalMatchQuantity = 0;

    while( it != idx.end() && order->comparePrice( *it ) && order->quantity > 0 )
    {
        const OrderPtr&  othOrder  = *it;
        //const TraderPtr& othTrader = othOrder->trader.lock();
        const quantity_t matchQty  = std::min( order->quantity, othOrder->quantity );

        order->quantity    -= matchQty;
        othOrder->quantity -= matchQty;
        totalMatchQuantity += matchQty;

        priceLevels.insert( othOrder->price );

        if( othOrder->quantity < 1 )
        {
            orders.template erase( it++ );
        }
        else
        {
            ++it;
        }
    }

    if( totalMatchQuantity > 0 )
    {
        priceLevels.insert( order->price );

        std::cout << "TRADE=" << totalMatchQuantity << "S=" << orders.template size() << std::endl;

        notifyPriceLevels<OrderContainer>( orders, priceLevels, matcher, order->side );
    }
}


template void OrderBook::handleExecution<BidOrderContainer>(
    BidOrderContainer::type& orders,
    const MatcherConstPtr& matcher,
    const TraderPtr& trader,
    const OrderPtr& order
);

template void OrderBook::handleExecution<AskOrderContainer>(
    AskOrderContainer::type& orders,
    const MatcherConstPtr& matcher,
    const TraderPtr& trader,
    const OrderPtr& order
);


} /* namespace pyxchange */



/* EOF */

