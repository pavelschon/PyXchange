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
template<typename OrderContainer, typename Pred>
void Matcher::handleExecution( OrderContainer& orders, const TraderPtr& trader, const OrderPtr& order, const OrdersCompare& comp )
{
    typename Orders::template index<tags::idxPriceTime>::type  const &idx        = orders.template get<tags::idxPriceTime>();
    typename Orders::template index<tags::idxPriceTime>::type::const_iterator it = idx.begin();

    quantity_t totalMatchQuantity = 0;

    std::set<price_t, Pred> priceLevels;

    while( it != idx.end() && comp( order, *it ) && order->quantity > 0 )
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
        std::cout << "TRADE=" << totalMatchQuantity << "S=" << orders.template size() << std::endl;

        //notifyPriceLevels( orders.template, priceLevels, order->side );
    }
}


template void Matcher::handleExecution<BidOrderContainer, higherPrice>(
    BidOrderContainer& orders, const TraderPtr& trader, const OrderPtr& order, const OrdersCompare& comp );

template void Matcher::handleExecution<AskOrderContainer, lowerPrice>(
    AskOrderContainer& orders, const TraderPtr& trader, const OrderPtr& order, const OrdersCompare& comp );


} /* namespace pyxchange */



/* EOF */

