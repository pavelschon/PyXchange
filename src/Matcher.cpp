/**
 * @brief This module implements simulator of exchange
 * @file Matcher.cpp
 * 
 */


#include "Matcher.hpp"
#include "orderbook/OrderBook.hpp"
#include "client/Client.hpp"
#include "client/Trader.hpp"
#include "Constants.hpp"
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
void Matcher::handleMessageImpl( const TraderPtr& trader, const std::string& data )
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

        handleMessageImpl( trader, decoded );
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
void Matcher::handleMessageImpl( const TraderPtr& trader, const py::dict& decoded )
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
TraderSet::const_iterator Matcher::findClient( const TraderPtr& trader ) const
{
    const auto& it = traders->find( trader );

    if( it == traders->cend() )
    {
        pyexc::raise( PyExc_KeyError, boost::format( format::f1::logTraderDoesNotExist ) % trader->toString() );
    }

    return it;
}


/**
 * @brief FIXME
 *
 */
ClientSet::const_iterator Matcher::findClient( const ClientPtr& client ) const
{
    const auto& it = clients->find( client );

    if( it == clients->cend() )
    {
        pyexc::raise( PyExc_KeyError, boost::format( format::f1::logClientDoesNotExist ) % client->toString() );
    }

    return it;
}


} /* namespace pyxchange */


/* EOF */

