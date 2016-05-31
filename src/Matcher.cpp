/**
 * @brief This module implements simulator of exchange
 * @file Matcher.cpp
 * 
 */


#include "Matcher.hpp"
#include "OrderBook.hpp"
#include "Json.hpp"
#include "Utils.hpp"


namespace pyxchange
{


namespace py = boost::python;


/**
 * @brief Constructor
 *
 */
Matcher::Matcher():
      orderbook{ std::make_shared<OrderBook>() }
{
    log( log::info, "Matcher is ready" );
}



/**
 * @brief Constructor
 * 
 */
Matcher::Matcher( const boost::python::object& logger_):
      orderbook{ std::make_shared<OrderBook>() }
    , logger{ logger_ }
{
    log( log::info, "Matcher is ready" );
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
void Matcher::handleMessageStr( const TraderPtr& trader, const std::string& data )
{
    if( checkRegistered( trader ) )
    {
        const py::dict decoded( json::loads( data ) );

        handleMessageImpl( trader, decoded );
    }
}


/**
 * @brief FIXME
 *
 */
void Matcher::handleMessageDict( const TraderPtr& trader, const py::dict& decoded )
{
    if( checkRegistered( trader ) )
    {
        handleMessageImpl( trader, decoded );
    }
}


/**
 * @brief FIXME
 *
 */
void Matcher::handleMessageImpl( const TraderPtr& trader, const py::dict& decoded )
{
    const py::str message_type( decoded[ keys::message ] );

    if( message_type == message::createOrder )
    {
        orderbook->createOrder( shared_from_this(), trader, decoded );
    }
    else if( message_type == message::cancelOrder )
    {
        orderbook->cancelOrder( shared_from_this(), trader, decoded );
    }
    else
    {
        trader->notifyError( strings::unknownMessage );

        PyErr_SetString( PyExc_KeyError, strings::unknownMessage.c_str() );

        py::throw_error_already_set();
    }
}


/**
 * @brief FIXME
 *
 */
void Matcher::addClient( const ClientPtr& client )
{
    if( ! clients.insert( client ).second )
    {
        client->notifyError( strings::clientAlreadyAdded );

        PyErr_SetString( PyExc_ValueError, strings::clientAlreadyAdded.c_str() );

        py::throw_error_already_set();
    }
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
    }
    else
    {
        client->notifyError( strings::clientDoesNotExist );

        PyErr_SetString( PyExc_KeyError, strings::clientDoesNotExist.c_str() );

        py::throw_error_already_set();
    }
}



/**
 * @brief FIXME
 *
 */
void Matcher::addTrader( const TraderPtr& trader )
{
    if( ! traders.insert( trader ).second )
    {
        trader->notifyError( strings::traderAlreadyAdded );

        PyErr_SetString( PyExc_ValueError, strings::traderAlreadyAdded.c_str() );

        py::throw_error_already_set();
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
        orderbook->cancelAllOrders( shared_from_this(), trader );

        traders.erase( it );
    }
    else
    {
        trader->notifyError( strings::traderDoesNotExist );

        PyErr_SetString( PyExc_KeyError, strings::traderDoesNotExist.c_str() );

        py::throw_error_already_set();
    }
}


/**
 * @brief FIXME
 *
 */
bool Matcher::checkRegistered( const TraderPtr& trader ) const
{
    const bool traderExist = traders.count( trader ) > 0;

    if( ! traderExist )
    {
        trader->notifyError( strings::traderDoesNotExist );

        PyErr_SetString( PyExc_KeyError, strings::traderDoesNotExist.c_str() );

        py::throw_error_already_set();
    }

    return traderExist;
}


} /* namespace pyxchange */


/* EOF */

