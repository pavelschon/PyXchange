/**
 * @brief This module implements simulator of exchange
 * @file OrderBook.cpp
 *
 */


#include "OrderBook.hpp"
#include "Matcher.hpp"
#include "Trader.hpp"


namespace pyxchange
{


namespace py = boost::python;


namespace format
{

const boost::format orderWrongSide( "order has wrong side" );

} /* namespace message */


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
        matcher->log( log::warning, format::orderWrongSide );

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
    else if( order->quantity < 1 )
    {

    }
    else if( order->price < 1 )
    {

    }
    else if( order->price < 1 )
    {

    }
}


} /* namespace pyxchange */



/* EOF */

