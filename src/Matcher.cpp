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
    if( Trader::checkRegistered( shared_from_this(), trader ) )
    {
        const py::dict decoded( json::loads( data ) );

        handleMessageImpl( trader, decoded );
    }
}


/**
 * @brief FIXME
 *
 */
void Matcher::handleMessageDict( const TraderPtr& trader, const boost::python::dict& decoded )
{
    if( Trader::checkRegistered( shared_from_this(), trader ) )
    {
        handleMessageImpl( trader, decoded );
    }
}


/**
 * @brief FIXME
 *
 */
void Matcher::handleMessageImpl( const TraderPtr& trader, const boost::python::dict& decoded )
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
size_t Matcher::cancelAllOrders( const TraderPtr& trader )
{
    return orderbook->cancelAllOrders( shared_from_this(), trader );
}


} /* namespace pyxchange */



/* EOF */

