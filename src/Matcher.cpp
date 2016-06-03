/**
 * @brief This module implements simulator of exchange
 * @file Matcher.cpp
 * 
 */


#include "Matcher.hpp"
#include "OrderBook.hpp"
#include "Constants.hpp"
#include "Client.hpp"
#include "Trader.hpp"
#include "Exception.hpp"
#include "Json.hpp"


namespace pyxchange
{

namespace py = boost::python;


/**
 * @brief Constructor
 *
 */
Matcher::Matcher():
      traders{ std::make_shared<TraderSet>() }
    , clients{ std::make_shared<ClientSet>() }
    , orderbook{ std::make_unique<OrderBook>( clients, logger ) }
{

}



/**
 * @brief Constructor
 * 
 */
Matcher::Matcher( const boost::python::object& logger_):
      logger{ logger_ }
    , traders{ std::make_unique<TraderSet>() }
    , clients{ std::make_shared<ClientSet>() }
    , orderbook{ std::make_unique<OrderBook>( clients, logger ) }
{
    logger.info( format::logMatcherReady );
}


/**
 * @brief FIXME
 *
 */
void Matcher::handleMessageStr( const TraderPtr& trader, const std::string& data )
{
    const auto exceptions{ PyExc_ValueError, PyExc_TypeError };
    const auto decode = std::bind( &json::loads<std::string, py::dict>, data );

    try
    {
        const py::dict decoded{ pyexc::translate<pyexc::JsonDecodeError>( decode, exceptions ) };

        handleMessageDict( trader, decoded );
    }
    catch( const pyexc::JsonDecodeError& )
    {
        logger.error( boost::format( format::jsonDecodeError ) % trader->getName() );

        trader->disconnect();
    }
}


/**
 * @brief FIXME
 *
 */
void Matcher::handleMessageDict( const TraderPtr& trader, const py::dict& decoded )
{
    try
    {
        const std::wstring message_ = extractMessage( decoded );

        if( message_ == message::wCreateOrder )
        {
            orderbook->createOrder( trader, decoded );
        }
        else if( message_ == message::wCancelOrder )
        {
            orderbook->cancelOrder( trader, decoded );
        }
    }
    catch( const pyexc::MalformedMessage& )
    {
        logger.error( boost::format( format::logMalformedMessage ) % trader->getName() );

        trader->disconnect();

        return;
    }
    catch( const pyexc::UnknownMessage& )
    {
        trader->notifyError( format::unknownMessage.str() );

        logger.error( boost::format( format::logUnknownMessage ) % trader->getName() );

        return;
    }
}


/**
 * @brief FIXME
 *
 */
std::wstring Matcher::extractMessage( const py::dict& decoded )
{
    const auto exceptions{ PyExc_KeyError, PyExc_TypeError };

    const auto decode = [ &decoded ]() {
        const std::wstring message_ = py::extract<std::wstring>( decoded[ keys::message ] );

        if( std::count( message::all.begin(), message::all.end(), message_ ) )
        {
            return message_;
        }

        throw pyexc::UnknownMessage();
    };

    return pyexc::translate<pyexc::MalformedMessage>( decode, exceptions );
}


/**
 * @brief FIXME
 *
 */
TraderPtr Matcher::getTrader( const std::string& name, const py::object& transport )
{
    const TraderPtr& trader = std::make_shared<Trader>( ( boost::format( format::trader ) % name ).str(), transport );

    traders->insert( trader );

    logger.info( boost::format( format::logGetClient ) % trader->getName() );

    return trader;
}


/**
 * @brief FIXME
 *
 */
void Matcher::removeTrader( const TraderPtr& trader )
{
    const auto& it = traders->find( trader );

    if( it != traders->cend() )
    {
        orderbook->cancelAllOrders( trader );

        traders->erase( it );

        logger.info( boost::format( format::logRemoveClient ) % trader->getName() );
    }
    else
    {
        logger.warning( boost::format( format::traderDoesNotExist ) % trader->getName() );
    }
}


/**
 * @brief FIXME
 *
 */
ClientPtr Matcher::getClient( const std::string& name, const py::object& transport )
{
    const ClientPtr& client = std::make_shared<Client>( ( boost::format( format::client ) % name ).str(), transport );

    clients->insert( client );

    logger.info( boost::format( format::logGetClient ) % client->getName() );

    return client;
}


/**
 * @brief FIXME
 *
 */
void Matcher::removeClient( const ClientPtr& client )
{
    const auto& it = clients->find( client );

    if( it != clients->cend() )
    {
        clients->erase( it );

        logger.info( boost::format( format::logRemoveClient ) % client->getName() );
    }
    else
    {
        logger.warning( boost::format( format::clientDoesNotExist ) % client->getName() );
    }
}


} /* namespace pyxchange */


/* EOF */

