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
    logger.info( format::f0::logMatcherReady );
}


/**
 * @brief FIXME
 *
 */
template<typename T>
void Matcher::handleMessageStr( const std::shared_ptr<T>& client,
                                const MatcherPtr& matcher, const std::string& data )
{
    matcher->handleMessageStr( client, data );
}


/**
 * @brief FIXME
 *
 */
template<typename T>
void Matcher::handleMessageDict( const std::shared_ptr<T>& client,
                                 const MatcherPtr& matcher, const boost::python::dict& decoded )
{
    matcher->handleMessageDict( client, decoded );
}


// template void Matcher::handleMessageStr(
//     const ClientPtr& client, const MatcherPtr& matcher, const std::string& data );
//
// template void Matcher::handleMessageDict(
//     const ClientPtr& client, const MatcherPtr& matcher, const boost::python::dict& decoded );

template void Matcher::handleMessageStr(
    const TraderPtr& trader, const MatcherPtr& matcher, const std::string& data );

template void Matcher::handleMessageDict(
    const TraderPtr& trader, const MatcherPtr& matcher, const boost::python::dict& decoded );


/**
 * @brief FIXME
 *
 */
void Matcher::handleMessageStr( const TraderPtr& trader, const std::string& data )
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

        handleMessageDict( trader, decoded );
    }
    catch( const pyexc::JsonDecodeError& )
    {
        logger.error( boost::format( format::f1::logJsonDecodeError ) % trader->toString() );

        trader->disconnect();
    }
    catch( const pyexc::JsonTooLong& )
    {
        logger.error( boost::format( format::f2::logJsonTooLong ) % trader->toString() % data.size() );

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
        logger.error( boost::format( format::f1::logMalformedMessage ) % trader->toString() );

        trader->disconnect();

        return;
    }
    catch( const pyexc::UnknownMessage& )
    {
        trader->notifyError( format::f0::unknownMessage.str() );

        logger.error( boost::format( format::f1::logUnknownMessage ) % trader->toString() );
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
        const std::wstring message_ = py::extract<const std::wstring>( decoded[ keys::message ] );

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
    const TraderPtr& trader = std::make_shared<Trader>(
        ( boost::format( format::f1::trader ) % name ).str(), transport );

    traders->insert( trader );

    logger.info( boost::format( format::f1::logGetClient ) % trader->toString() );

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

        logger.info( boost::format( format::f1::logRemoveClient ) % trader->toString() );
    }
    else
    {
        logger.warning( boost::format( format::f1::logTraderDoesNotExist ) % trader->toString() );
    }
}


/**
 * @brief FIXME
 *
 */
ClientPtr Matcher::getClient( const std::string& name, const py::object& transport )
{
    const ClientPtr& client = std::make_shared<Client>(
        ( boost::format( format::f1::client ) % name ).str(), transport );

    clients->insert( client );

    orderbook->aggregateAllPriceLevels( client );

    logger.info( boost::format( format::f1::logGetClient ) % client->toString() );

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

        logger.info( boost::format( format::f1::logRemoveClient ) % client->toString() );
    }
    else
    {
        logger.warning( boost::format( format::f1::logClientDoesNotExist ) % client->toString() );
    }
}


} /* namespace pyxchange */


/* EOF */

