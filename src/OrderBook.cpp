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
    const auto& order = std::make_shared<Order>( trader, params... );
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
    const auto& order  = result.first;

    if( !result.second )
    {
        trader->notifyCreateOrderError( order->orderId, strings::orderAlreadyExist );

        PyErr_SetString( PyExc_ValueError, strings::orderAlreadyExist.c_str() );

        py::throw_error_already_set();
    }
    else if( order->isBid() )
    {
        trader->notifyCreateOrderSuccess( order->orderId );

        handleExecution<AskOrderContainer>( askOrders, matcher, trader, order );

        if( order->quantity )
        {
            bidOrders.insert( order );
        }
    }
    else if( order->isAsk() )
    {
        trader->notifyCreateOrderSuccess( order->orderId );

        handleExecution<BidOrderContainer>( bidOrders, matcher, trader, order );

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

    if( trader->cancelOrder( orderId ) )
    {
        trader->notifyCancelOrderSuccess( orderId );
    }
    else
    {
        trader->notifyCancelOrderError( orderId, strings::orderDoesNotExist );

        PyErr_SetString( PyExc_ValueError, strings::orderDoesNotExist.c_str() );

        py::throw_error_already_set();
    }
}


} /* namespace pyxchange */



/* EOF */

