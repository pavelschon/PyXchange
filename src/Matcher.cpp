/**
 * @brief This module implements simulator of exchange
 * @file Matcher.cpp
 * 
 */


#include "Matcher.hpp"
#include "Client.hpp"
#include "Trader.hpp"
#include "Json.hpp"


namespace pyxchange
{


namespace py = boost::python;


namespace format
{

const boost::format client( "<Client %||>" );
const boost::format trader( "<Trader %||>" );
const boost::format clientDoesNotExist( "%|| does not exists" );
const boost::format traderDoesNotExist( "%|| does not exists" );
const boost::format logMatcherReady( "Matcher is ready" );
const boost::format logGetClient( "%|| created" );
const boost::format logRemoveClient( "%|| removed" );


} /* namespace message */


namespace message
{

const std::string createOrder        = "createOrder";
const std::string cancelOrder        = "cancelOrder";

} /* namespace message */


/**
 * @brief Constructor
 *
 */
Matcher::Matcher()
{

}



/**
 * @brief Constructor
 * 
 */
Matcher::Matcher( const boost::python::object& logger_):
    logger{ logger_ }
{
    log( log::info, format::logMatcherReady );
}


/**
 * @brief FIXME
 *
 */
void Matcher::log( const std::string& level, const std::string& message ) const
{
    if( logger != py::object() ) // if logger is not None
    {
        logger.attr( level.c_str() )( message );
    }
}


/**
 * @brief FIXME
 *
 */
void Matcher::log( const std::string& level, const boost::format& message ) const
{
    if( logger != py::object() ) // if logger is not None
    {
        logger.attr( level.c_str() )( message.str() );
    }
}


/**
 * @brief FIXME
 *
 */
void Matcher::handleMessageStr( const TraderPtr& trader, const std::string& data )
{
    const py::dict decoded( json::loads( data ) );

    handleMessageDict( trader, decoded );
}


/**
 * @brief FIXME
 *
 */
void Matcher::handleMessageDict( const TraderPtr& trader, const py::dict& decoded )
{
    const py::str message_type( decoded[ keys::message ] );

    if( message_type == message::createOrder )
    {
        orderbook.createOrder( shared_from_this(), trader, decoded );
    }
    else if( message_type == message::cancelOrder )
    {
        orderbook.cancelOrder( shared_from_this(), trader, decoded );
    }
    else
    {
        log( log::warning, strings::unknownMessage );

        trader->notifyError( strings::unknownMessage );
        trader->disconnect();
    }
}


/**
 * @brief FIXME
 *
 */
ClientPtr Matcher::getClient( const std::string& name, const boost::python::object& transport )
{
    const ClientPtr& client = std::make_shared<Client>( ( boost::format( format::client ) % name ).str(), transport );

    clients.insert( client );

    log( log::info, boost::format( format::logGetClient ) % client->getName() );

    return client;
}


/**
 * @brief FIXME
 *
 */
TraderPtr Matcher::getTrader( const std::string& name, const boost::python::object& transport )
{
    const TraderPtr& trader = std::make_shared<Trader>( ( boost::format( format::trader ) % name ).str(), transport );

    traders.insert( trader );

    log( log::info, boost::format( format::logGetClient ) % trader->getName() );

    return trader;
}


/**
 * @brief FIXME
 *
 */
void Matcher::removeClient( const ClientPtr& client )
{
    const auto& it = clients.find( client );

    if( it != clients.cend() )
    {
        clients.erase( it );

        log( log::info, boost::format( format::logRemoveClient ) % client->getName() );
    }
    else
    {
        log( log::warning, boost::format( format::traderDoesNotExist ) % client->getName() );
    }
}


/**
 * @brief FIXME
 *
 */
void Matcher::removeTrader( const TraderPtr& trader )
{
    const auto& it = traders.find( trader );

    if( it != traders.cend() )
    {
        orderbook.cancelAllOrders( shared_from_this(), trader );

        traders.erase( it );

        log( log::info, boost::format( format::logRemoveClient ) % trader->getName() );
    }
    else
    {
        log( log::warning, boost::format( format::traderDoesNotExist ) % trader->getName() );
    }
}


/**
 * @brief FIXME
 *
 */
void Matcher::notifyAllClients( const boost::python::object& data ) const
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

