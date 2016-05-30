/**
 * @brief This module implements simulator of exchange
 * @file OrderBook.cpp
 *
 */


#include "OrderBook.hpp"
#include "Client.hpp"
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
void OrderBook::createOrder( const MatcherPtr& matcher, const TraderPtr& trader, const boost::python::dict& decoded )
{
    const auto& order = std::make_shared<Order>( trader, decoded );

    if( order->isBid() && bidOrders.insert( order ).second )
    {
        trader->notifyCreateOrderSuccess( order->orderId );

        handleExecution<AskOrderContainer>( askOrders, matcher, trader, order );

        if( order->price > 0 )
        {
            aggregatePriceLevel<BidOrderContainer>( bidOrders, matcher, order->price, order->side );
        }
    }
    else if( order->isAsk() && askOrders.insert( order ).second )
    {
        trader->notifyCreateOrderSuccess( order->orderId );

        handleExecution<BidOrderContainer>( bidOrders, matcher, trader, order );

        if( order->price > 0 )
        {
            aggregatePriceLevel<AskOrderContainer>( askOrders, matcher, order->price, order->side );
        }
    }
    else
    {
        trader->notifyCreateOrderError( order->orderId, strings::orderAlreadyExist );

        PyErr_SetString( PyExc_ValueError, strings::orderAlreadyExist.c_str() );

        py::throw_error_already_set();
    }
}


} /* namespace pyxchange */



/* EOF */

