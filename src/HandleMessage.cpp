/**
 * @brief This module implements simulator of exchange
 * @file HandleMessage.cpp
 *
 */


#include "Matcher.hpp"
#include "Client.hpp"
#include "Trader.hpp"
#include "Utils.hpp"


namespace pyxchange
{


namespace py = boost::python;




/**
 * @brief FIXME
 *
 */
void Matcher::handleMessageStr( const TraderPtr& trader, const char* const data )
{
    if( checkTraderExist( trader ) )
    {
        const py::dict decoded( json_loads( data ) );

        handleMessageImpl( trader, decoded );
    }
}


/**
 * @brief FIXME
 *
 */
void Matcher::handleMessageDict( const TraderPtr& trader, const boost::python::dict& decoded )
{
    if( checkTraderExist( trader ) )
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
        createOrder( trader, decoded );
    }
    else if( message_type == message::cancelOrder )
    {
        cancelOrder( trader, decoded );
    }
    else
    {
        trader->notifyError( strings::unknownMessage );

        PyErr_SetString( PyExc_KeyError, strings::unknownMessage );

        py::throw_error_already_set();
    }
}


} /* namespace pyxchange */



/* EOF */

