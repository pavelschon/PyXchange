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
 * @brief Constructor
 *
 */
OrderBook::OrderBook()
{

}


/**
 * @brief FIXME
 *
 */
template<typename... Params>
OrderCreateResult Trader::createOrder( const TraderPtr& trader, Params... params )
{
    const OrderPtr& order = std::make_shared<Order>( trader, params... );
    const auto& orderPair = std::make_pair( order->getId(), order );
    const auto& insResult = trader->orders.insert( orderPair );

    return std::make_pair( order, insResult.second );
}


/**
 * @brief FIXME
 *
 */
void OrderBook::createOrder( const MatcherPtr& matcher, const TraderPtr& trader, const boost::python::dict& decoded )
{
    const auto& result = Trader::createOrder( trader, decoded );
    const OrderPtr& order = result.first;

    if( !result.second )
    {
        trader->notifyCreateOrderError( order->orderId );
    }
    else if( order->side == side::bid )
    {
        trader->notifyCreateOrderSuccess( order->orderId );

        handleExecution<AskOrderContainer>( askOrders, trader, order );

        if( order->quantity )
        {
            bidOrders.insert( order );
        }
    }
    else if( order->side == side::ask )
    {
        trader->notifyCreateOrderSuccess( order->orderId );

        handleExecution<BidOrderContainer>( bidOrders, trader, order );

        if( order->quantity )
        {
            askOrders.insert( order );
        }
    }
}


/**
 * @brief FIXME
 *
 */
void OrderBook::cancelOrder( const MatcherPtr& matcher, const TraderPtr& trader, const boost::python::dict& decoded )
{
    const orderId_t orderId = py::extract<const orderId_t>( decoded[ keys::orderId ] );

    if( ! trader->cancelOrder( orderId ) )
    {
        trader->notifyCancelOrderError( orderId );
    }
    else
    {
        trader->notifyCancelOrderSuccess( orderId );
    }
}


} /* namespace pyxchange */



/* EOF */

