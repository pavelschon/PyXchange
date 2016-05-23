/**
 * @brief This module implements simulator of exchange
 * @file CancelOrder.cpp
 *
 */


#include "Matcher.hpp"
#include "MatcherUtils.hpp"

#include <iostream>


namespace pyxchange
{

namespace py = boost::python;


/**
 * @brief FIXME
 *
 */
void Matcher::handleBidExecution( const TraderPtr& bidTrader, const OrderPtr& bidOrder )
{
    AskOrderContainer::index<tags::idxPriceTime>::type const &idx = askOrders.get<tags::idxPriceTime>();
    AskOrderContainer::index<tags::idxPriceTime>::type::const_iterator it = idx.begin();

    quantity_t totalMatchQuantity = 0;

    std::set<price_t, lowerPrice> priceLevels;

    while( it != idx.end() && bidOrder->price >= (*it)->price && bidOrder->quantity > 0 )
    {
        const OrderPtr&  askOrder  = *it;
        const TraderPtr& askTrader = askOrder->trader.lock();
        const quantity_t matchQty  = std::min( bidOrder->quantity, askOrder->quantity );

        askOrder->quantity -= matchQty;
        bidOrder->quantity -= matchQty;
        totalMatchQuantity += matchQty;

        priceLevels.insert( askOrder->price );

        if( askOrder->quantity < 1 )
        {
            askOrders.erase( it++ );
        }
        else
        {
            ++it;
        }
    }

    if( totalMatchQuantity > 0 )
    {
        std::cout << "TRADE=" << totalMatchQuantity << "S=" << askOrders.size() << std::endl;

        notifyPriceLevels( askOrders, priceLevels, side::ask );
    }
}



/**
 * @brief FIXME
 *
 */
void Matcher::handleAskExecution( const TraderPtr& bidTrader, const OrderPtr& askOrder )
{
    BidOrderContainer::index<tags::idxPriceTime>::type const &idx= bidOrders.get<tags::idxPriceTime>();
    BidOrderContainer::index<tags::idxPriceTime>::type::const_iterator it = idx.begin();

    quantity_t totalMatchQuantity = 0;

    std::set<price_t, higherPrice> priceLevels;

    while( it != idx.end() && askOrder->price <= (*it)->price && askOrder->quantity > 0 )
    {
        const OrderPtr&  bidOrder  = *it;
        const TraderPtr& bidTrader = bidOrder->trader.lock();
        const quantity_t matchQty  = std::min( bidOrder->quantity, askOrder->quantity );

        askOrder->quantity -= matchQty;
        bidOrder->quantity -= matchQty;
        totalMatchQuantity += matchQty;

        priceLevels.insert( bidOrder->price );

        if( bidOrder->quantity < 1 )
        {
            bidOrders.erase( it++ );
        }
        else
        {
            ++it;
        }
    }

    if( totalMatchQuantity > 0 )
    {
        std::cout << "TRADE=" << totalMatchQuantity << std::endl;

        notifyPriceLevels( bidOrders, priceLevels, side::bid );
    }
}


} /* namespace pyxchange */



/* EOF */

