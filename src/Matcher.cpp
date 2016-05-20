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

        boost::python::throw_error_already_set();
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

        boost::python::throw_error_already_set();
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

        boost::python::throw_error_already_set();
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

        boost::python::throw_error_already_set();
    }
}


} /* namespace pyxchange */



/* EOF */

