/**
 * @brief This module implements simulator of exchange
 * @file OrderBook.cpp
 *
 */


#include "OrderBook.hpp"
#include "Client.hpp"
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
OrderBook::OrderBook( const ClientSetConstPtr & clients_ ):
    clients{ clients_ }
{

}


/**
 * @brief Constructor
 *
 */
OrderBook::OrderBook( const ClientSetConstPtr & clients_, const Logger& logger_ ):
      logger{ logger_ }
    , clients{ clients_ }
{

}


/**
 * @brief FIXME
 *
 */
void OrderBook::createOrder( const TraderPtr& trader, const py::dict& decoded )
{
    OrderPtr order;

    try
    {
        order = std::make_shared<Order>( trader, decoded );
    }
    catch( const side::WrongSide& )
    {
        logger.warning( format::orderWrongSide );

        trader->notifyError( strings::unknownSide );

        return;
    }

    if( order->isBid() && order->quantity > 0 )
    {
        insertOrder<BidOrderContainer, AskOrderContainer>( bidOrders, askOrders, trader, order );
    }
    else if( order->isAsk() && order->quantity > 0 )
    {
        insertOrder<AskOrderContainer, BidOrderContainer>( askOrders, bidOrders, trader, order );
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



/**
 * @brief FIXME
 *
 */
void OrderBook::notifyAllClients( const boost::python::object& data ) const
{
    for( const auto& client : *clients )
    {
        const auto& client_ = client.lock(); // from weak_ptr to shared_ptr

        if( client_ )
        {
            client_->writeData( data );
        }
    }
}


} /* namespace pyxchange */



/* EOF */

