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
Matcher::Matcher(): orderbook{ std::make_shared<OrderBook>() }
{

}


/**
 * @brief FIXME
 *
 */
void Matcher::handleMessageStr( const MatcherPtr& matcher, const TraderPtr& trader, const std::string& data )
{
    if( Trader::checkRegistered( matcher, trader ) )
    {
        const py::dict decoded( json::loads( data ) );

        handleMessageImpl( matcher, trader, decoded );
    }
}


/**
 * @brief FIXME
 *
 */
void Matcher::handleMessageDict( const MatcherPtr& matcher, const TraderPtr& trader, const boost::python::dict& decoded )
{
    if( Trader::checkRegistered( matcher, trader ) )
    {
        handleMessageImpl( matcher, trader, decoded );
    }
}


/**
 * @brief FIXME
 *
 */
void Matcher::handleMessageImpl( const MatcherPtr& matcher, const TraderPtr& trader, const boost::python::dict& decoded )
{
    const py::str message_type( decoded[ keys::message ] );

    if( message_type == message::createOrder )
    {
        matcher->orderbook->createOrder( matcher, trader, decoded );
    }
    else if( message_type == message::cancelOrder )
    {
        matcher->orderbook->cancelOrder( matcher, trader, decoded );
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
size_t Matcher::cancelAllOrders( const MatcherPtr& matcher, const TraderPtr& trader )
{
    return matcher->orderbook->cancelAllOrders( matcher, trader );
}


} /* namespace pyxchange */



/* EOF */

