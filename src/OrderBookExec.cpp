/**
 * @brief This module implements simulator of exchange
 * @file OrderBook.cpp
 *
 */


#include "OrderBook.hpp"
#include "Trader.hpp"
#include "Utils.hpp"


namespace pyxchange
{


namespace py = boost::python;


/**
 * @brief FIXME
 *
 */
template<typename OrderContainer>
void OrderBook::handleExecution( typename OrderContainer::type& orders, const MatcherConstPtr& matcher,
                                 const TraderPtr& trader, const OrderPtr& order )
{
    typename OrderContainer::price_set priceLevels;

    auto &idx = orders.template get<tags::idxPriceTime>();
    auto it   = idx.begin();

    quantity_t totalMatchQuantity = 0;

    while( it != idx.end() && order->comparePrice( *it ) && order->quantity > 0 )
    {
        const auto& oppOrder = *it;
        //const TraderPtr& oppTrader = oppOrder->getTrader();
        const quantity_t matchQty  = std::min( order->quantity, oppOrder->quantity );

        order->quantity    -= matchQty;
        oppOrder->quantity -= matchQty;
        totalMatchQuantity += matchQty;

        priceLevels.insert( oppOrder->price );

        if( oppOrder->quantity < 1 )
        {
            idx.erase( it++ );
        }
        else
        {
            ++it;
        }
    }

    if( totalMatchQuantity > 0 )
    {
        std::cout << "TRADE=" << totalMatchQuantity << "S=" << orders.template size() << std::endl;

        aggregateAllPriceLevels<OrderContainer>( orders, priceLevels, matcher, side::opposite( order->side ) );
    }
}



/**
 * @brief FIXME
 *
 */
template<typename OrderContainer>
void OrderBook::handleSelfMatch( const typename OrderContainer::type& orders, const MatcherConstPtr& matcher,
                                 const TraderPtr& trader, const OrderConstPtr& order ) const
{
    Order order_( *order ); // copy of order
    auto &idx = orders.template get<tags::idxPriceTime>();
    auto it   = idx.begin();

    while( it != idx.end() && order_.comparePrice( *it ) && order_.quantity > 0 )
    {
        const auto& oppOrder = *it;

        if( trader == oppOrder->getTrader() )
        {
            trader->notifyCreateOrderError( order_.orderId, strings::orderSelfMatch );

            PyErr_SetString( PyExc_ValueError, strings::orderSelfMatch.c_str() );

            py::throw_error_already_set();
        }

        order_.quantity -= std::min( order_.quantity, oppOrder->quantity );
    }
}


template void OrderBook::handleExecution<BidOrderContainer>(
    BidOrderContainer::type& orders, const MatcherConstPtr& matcher,
    const TraderPtr& trader, const OrderPtr& order );

template void OrderBook::handleExecution<AskOrderContainer>(
    AskOrderContainer::type& orders, const MatcherConstPtr& matcher,
    const TraderPtr& trader, const OrderPtr& order );

template void OrderBook::handleSelfMatch<BidOrderContainer>(
    const BidOrderContainer::type& orders, const MatcherConstPtr& matcher,
    const TraderPtr& trader, const OrderConstPtr& order ) const;

template void OrderBook::handleSelfMatch<AskOrderContainer>(
    const AskOrderContainer::type& orders, const MatcherConstPtr& matcher,
    const TraderPtr& trader, const OrderConstPtr& order ) const;

} /* namespace pyxchange */



/* EOF */

