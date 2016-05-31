/**
 * @brief This module implements simulator of exchange
 * @file OrderBook.cpp
 *
 */


#include "OrderBook.hpp"
#include "Matcher.hpp"
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
    OrderPtr order;

    try
    {
        order = std::make_shared<Order>( trader, decoded );
    }
    catch( const side::WrongSide& )
    {
        trader->notifyError( strings::unknownSide );

        return;
    }

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
        matcher->log( log::warning, strings::orderInvalid );

        trader->notifyCreateOrderError( order->orderId, strings::orderInvalid );
        trader->disconnect();
    }
}


} /* namespace pyxchange */



/* EOF */

