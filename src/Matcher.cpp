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
        trader->notifyError( strings::traderAlreadyAdded );

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
        client->notifyError( strings::clientAlreadyAdded );

        PyErr_SetString( PyExc_ValueError, strings::clientAlreadyAdded );

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
        traders.erase( it );
    }
    else
    {
        trader->notifyError( strings::traderDoesNotExist );

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
        client->notifyError( strings::clientDoesNotExist );

        PyErr_SetString( PyExc_KeyError, strings::clientDoesNotExist );

        py::throw_error_already_set();
    }
}


/**
 * @brief FIXME
 *
 */
bool Matcher::checkTraderExist( const TraderPtr& trader ) const
{
    const auto traderExist = traders.count( trader ) > 0;

    if( ! traderExist )
    {
        trader->notifyError( strings::traderDoesNotExist );

        PyErr_SetString( PyExc_KeyError, strings::traderDoesNotExist );

        py::throw_error_already_set();
    }

    return traderExist;
}


} /* namespace pyxchange */



/* EOF */

