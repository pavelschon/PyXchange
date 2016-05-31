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
void OrderBook::createOrder( const MatcherConstPtr& matcher, const TraderPtr& trader, const py::dict& decoded )
{
    const auto& order = std::make_shared<Order>( trader, decoded );

    if( order->isBid() && order->quantity > 0 )
    {
        insertOrder<BidOrderContainer, AskOrderContainer>( bidOrders, askOrders, matcher, trader, order );
    }
    else if( order->isAsk() && order->quantity > 0 )
    {
        insertOrder<AskOrderContainer, BidOrderContainer>( askOrders, bidOrders, matcher, trader, order );
    }
    else
    {
        trader->notifyCreateOrderError( order->orderId, strings::orderInvalid );

        PyErr_SetString( PyExc_ValueError, strings::orderInvalid.c_str() );

        py::throw_error_already_set();
    }
}


} /* namespace pyxchange */



/* EOF */

