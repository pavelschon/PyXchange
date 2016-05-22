/**
 * @brief This module implements simulator of exchange
 * @file CancelOrder.cpp
 *
 */


#include "OrderBook.hpp"
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
void OrderBook::handleBidExecution( const TraderPtr& bidTrader, const OrderPtr& bidOrder )
{
    using namespace boost::multi_index;

    typename AskOrderContainer::template index<idxPriceTime>::type &idx = askOrders.get<idxPriceTime>();
    typename AskOrderContainer::template index<idxPriceTime>::type::const_iterator it = idx.begin();

    quantity_t totalMatchQuantity = 0;

    while( it != idx.end() && bidOrder->price >= (*it)->price && bidOrder->quantity > 0 )
    {
        const OrderPtr&  askOrder  = *it;
        const TraderPtr& askTrader = askOrder->trader.lock();
        const quantity_t matchQty  = std::min( bidOrder->quantity, askOrder->quantity );

        askOrder->quantity -= matchQty;
        bidOrder->quantity -= matchQty;
        totalMatchQuantity += matchQty;

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
    }
}



/**
 * @brief FIXME
 *
 */
void OrderBook::handleAskExecution( const TraderPtr& bidTrader, const OrderPtr& askOrder )
{
    using namespace boost::multi_index;

    typename BidOrderContainer::template index<idxPriceTime>::type &idx = bidOrders.get<idxPriceTime>();
    typename BidOrderContainer::template index<idxPriceTime>::type::const_iterator it = idx.begin();

    quantity_t totalMatchQuantity = 0;

    while( it != idx.end() && askOrder->price <= (*it)->price && askOrder->quantity > 0 )
    {
        const OrderPtr&  bidOrder  = *it;
        const TraderPtr& bidTrader = bidOrder->trader.lock();
        const quantity_t matchQty  = std::min( bidOrder->quantity, askOrder->quantity );

        askOrder->quantity -= matchQty;
        bidOrder->quantity -= matchQty;
        totalMatchQuantity += matchQty;

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
    }
}


} /* namespace pyxchange */



/* EOF */

