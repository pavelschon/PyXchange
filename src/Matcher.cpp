/**
 * @brief This module implements simulator of exchange
 * @file Matcher.cpp
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
        PyErr_SetString( PyExc_ValueError, "trader already added" );

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
        PyErr_SetString( PyExc_ValueError, "client already added" );

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
        PyErr_SetString( PyExc_KeyError, "trader does not exist" );

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
        PyErr_SetString( PyExc_KeyError, "client does not exist" );

        py::throw_error_already_set();
    }
}


/**
 * @brief FIXME
 *
 */
void Matcher::handleMessage( const TraderPtr& trader, const char* const data )
{
    const py::dict decoded( json_loads( data ) );
    const py::str message_type( decoded["message"] );

    if( message_type == message::createOrder )
    {
        orderbook.createOrder( trader, decoded );
    }
    else
    {
        PyErr_SetString( PyExc_KeyError, "unknown message" );

        py::throw_error_already_set();
    }
}


} /* namespace pyxchange */



/* EOF */

