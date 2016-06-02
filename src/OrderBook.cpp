/**
 * @brief This module implements simulator of exchange
 * @file OrderBook.cpp
 *
 */


#include "OrderBook.hpp"
#include "Matcher.hpp"
#include "Client.hpp"
#include "Trader.hpp"


namespace pyxchange
{


namespace py = boost::python;


namespace format
{

const boost::format client( "<Client %||>" );
const boost::format logGetClient( "%|| created" );
const boost::format logRemoveClient( "%|| removed" );
const boost::format clientDoesNotExist( "%|| does not exists" );
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
 * @brief Constructor
 *
 */
OrderBook::OrderBook( const Logger& logger_ ):
    logger{ logger_ }
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
ClientPtr OrderBook::getClient( const MatcherPtr& matcher, const std::string& name, const boost::python::object& transport )
{
    const ClientPtr& client = std::make_shared<Client>( ( boost::format( format::client ) % name ).str(), transport );

    matcher->orderbook.clients.insert( client );

    matcher->orderbook.logger.info( boost::format( format::logGetClient ) % client->getName() );

    return client;
}


/**
 * @brief FIXME
 *
 */
void OrderBook::removeClient( const MatcherPtr& matcher, const ClientPtr& client )
{
    const auto& it = matcher->orderbook.clients.find( client );

    if( it != matcher->orderbook.clients.cend() )
    {
        matcher->orderbook.clients.erase( it );

        matcher->orderbook.logger.info( boost::format( format::logRemoveClient ) % client->getName() );
    }
    else
    {
        matcher->orderbook.logger.warning( boost::format( format::clientDoesNotExist ) % client->getName() );
    }
}



/**
 * @brief FIXME
 *
 */
void OrderBook::notifyAllClients( const boost::python::object& data ) const
{
    for( const auto& client : clients )
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

