/**
 * @brief This module implements simulator of exchange
 * @file Matcher.cpp
 * 
 */


#include "Matcher.hpp"
#include "Client.hpp"
#include "Trader.hpp"
#include "Utils.hpp"

#include <chrono>


namespace pyxchange
{


namespace py = boost::python;


/**
 * @brief Constructor
 * 
 */
Matcher::Matcher()
{

}


/**
 * @brief FIXME
 *
 */
void Matcher::addTrader( const TraderPtr& trader )
{
    if( ! traders.insert( trader ).second )
    {
        PyErr_SetString( PyExc_ValueError, strings::traderAlreadyAdded );

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
        PyErr_SetString( PyExc_ValueError, strings::clientAlreadyAdded );

        py::throw_error_already_set();
    }
}



/**
 * @brief FIXME
 *
 */
void Matcher::removeTrader( const TraderPtr& client )
{
    const auto& it = traders.find( client );

    if( it != traders.cend() )
    {
        traders.erase( it );
    }
    else
    {
        PyErr_SetString( PyExc_KeyError, strings::traderDoesNotExist );

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
        PyErr_SetString( PyExc_KeyError, strings::clientDoesNotExist );

        py::throw_error_already_set();
    }
}

/**
 * @brief FIXME
 *
 */
void Matcher::handleMessageStr( const TraderPtr& trader, const char* const data )
{
    const py::dict decoded( json_loads( data ) );

    handleMessageDict( trader, decoded );
}


/**
 * @brief FIXME
 *
 */
void Matcher::handleMessageDict( const TraderPtr& trader, const boost::python::dict& decoded )
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
        PyErr_SetString( PyExc_KeyError, strings::unknownMessage );

        py::throw_error_already_set();
    }
}


} /* namespace pyxchange */



/* EOF */

