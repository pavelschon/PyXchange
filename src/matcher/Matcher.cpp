/**
 * @brief This module implements simulator of exchange
 * @file Matcher.cpp
 * 
 */


#include "matcher/Matcher.hpp"
#include "orderbook/OrderBook.hpp"
#include "client/Client.hpp"
#include "client/Trader.hpp"
#include "utils/Constants.hpp"
#include "utils/Exception.hpp"
#include "utils/Json.hpp"


namespace pyxchange
{

namespace py = boost::python;


/**
 * @brief Constructor
 *
 */
Matcher::Matcher():
      clients{ std::make_shared<ClientVector>() }
    , orderbook{ std::make_unique<OrderBook>( clients, logger ) }
{

}


/**
 * @brief Constructor
 * 
 */
Matcher::Matcher( const boost::python::object& logger_):
      logger{ logger_ }
    , clients{ std::make_shared<ClientVector>() }
    , orderbook{ std::make_unique<OrderBook>( clients, logger ) }
{
    logger.info( format::f0::logMatcherReady );
}


/**
 * @brief FIXME
 *
 */
void Matcher::handleCreateOrder( const TraderPtr& trader, const boost::python::dict& decoded )
{
    trader->matcher->orderbook->createOrder( trader, decoded );
}


/**
 * @brief FIXME
 *
 */
void Matcher::handleCancelOrder( const TraderPtr& trader, const boost::python::dict& decoded )
{
    trader->matcher->orderbook->cancelOrder( trader, decoded );
}


/**
 * @brief FIXME
 *
 */
void Matcher::handleCancelAll( const TraderPtr& trader )
{
    trader->matcher->orderbook->cancelAllOrders( trader );
}


/**
 * @brief FIXME
 *
 */
ClientPtr Matcher::makeClient( const MatcherPtr& matcher, const std::string& name, const py::object& transport )
{
    const ClientPtr& client = std::make_shared<Client>( matcher, name, transport );

    matcher->clients->push_back( client );
    matcher->orderbook->aggregateAllPriceLevels( client );

    return client;
}


/**
 * @brief FIXME
 *
 */
template<typename CLIENT>
void Matcher::handleMessageImpl( const CLIENT& client, const std::string& data )
{
    const auto exceptions{ PyExc_ValueError, PyExc_TypeError };
    const auto decode = std::bind( &json::loads<const std::string, py::dict>, data );

    try
    {
        if( data.size() > json::maxJsonSize )
        {
            throw pyexc::JsonTooLong();
        }

        const py::dict decoded{ pyexc::translate<pyexc::JsonDecodeError>( decode, exceptions ) };

        handleMessageImpl( client, decoded );
    }
    catch( const pyexc::JsonDecodeError& )
    {
        logger.error( boost::format( format::f1::logJsonDecodeError ) % client->toString() );

        client->disconnect();
    }
    catch( const pyexc::JsonTooLong& )
    {
        logger.error( boost::format( format::f2::logJsonTooLong ) % client->toString() % data.size() );

        client->disconnect();
    }
}


/**
 * @brief FIXME
 *
 */
template<typename CLIENT>
void Matcher::handleMessageImpl( const CLIENT& client, const py::dict& decoded )
{
    try
    {
        const std::wstring message_ = extractMessage( client->messages, decoded );

        handleMessageImpl( client, decoded, message_ );
    }
    catch( const pyexc::MalformedMessage& )
    {
        logger.error( boost::format( format::f1::logMalformedMessage ) % client->toString() );

        client->disconnect();

        return;
    }
    catch( const pyexc::UnknownMessage& )
    {
        client->notifyError( format::f0::unknownMessage.str() );

        logger.error( boost::format( format::f1::logUnknownMessage ) % client->toString() );
    }
}


/**
 * @brief FIXME
 *
 */
void Matcher::handleMessageImpl( const TraderPtr& trader, const py::dict& decoded, const std::wstring message_ )
{
    if( message_ == message::wPing )
    {
        trader->notifyPong();
    }
    else if( message_ == message::wCreateOrder )
    {
        orderbook->createOrder( trader, decoded );
    }
    else if( message_ == message::wCancelOrder )
    {
        orderbook->cancelOrder( trader, decoded );
    }
    else if( message_ == message::wCancelAll )
    {
        orderbook->cancelAllOrders( trader );
    }
}


/**
 * @brief FIXME
 *
 */
void Matcher::handleMessageImpl( const ClientPtr& client, const py::dict& decoded, const std::wstring message_ )
{
    if( message_ == message::wPing )
    {
        client->notifyPong();
    }
}


/**
 * @brief FIXME
 *
 */
std::wstring Matcher::extractMessage( const MessageVector& messages, const py::dict& decoded )
{
    const auto exceptions{ PyExc_KeyError, PyExc_TypeError };

    const auto decode = [ &messages, &decoded ]() {
        const std::wstring message_ = py::extract<const std::wstring>( decoded[ keys::message ] );

        if( std::count( messages.begin(), messages.end(), message_ ) )
        {
            return message_;
        }

        throw pyexc::UnknownMessage();
    };

    return pyexc::translate<pyexc::MalformedMessage>( decode, exceptions );
}


template void Matcher::handleMessageImpl( const ClientPtr& client, const std::string& data );
template void Matcher::handleMessageImpl( const TraderPtr& trader, const std::string& data );

template void Matcher::handleMessageImpl( const ClientPtr& client, const py::dict& data );
template void Matcher::handleMessageImpl( const TraderPtr& trader, const py::dict& data );


} /* namespace pyxchange */


/* EOF */

