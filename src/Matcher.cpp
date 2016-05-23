/**
 * @brief This module implements simulator of exchange
 * @file Matcher.cpp
 * 
 */


#include "Matcher.hpp"
#include "MatcherUtils.hpp"


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
        notifyError( trader, strings::traderAlreadyAdded );

        PY_THROW_ERROR_IF( true, PyExc_ValueError, strings::traderAlreadyAdded );
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
        notifyError( client, strings::clientAlreadyAdded );

        PY_THROW_ERROR_IF( true, PyExc_ValueError, strings::clientAlreadyAdded );
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
        notifyError( trader, strings::traderDoesNotExist );

        PY_THROW_ERROR_IF( true, PyExc_KeyError, strings::traderDoesNotExist );
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
        notifyError( client, strings::clientDoesNotExist );

        PY_THROW_ERROR_IF( true, PyExc_KeyError, strings::clientDoesNotExist );
    }
}


/**
 * @brief FIXME
 *
 */
bool Matcher::checkTraderExist( const TraderPtr& trader )
{
    const auto traderExist = traders.count( trader ) > 0;

    if( ! traderExist )
    {
        notifyError( trader, strings::traderDoesNotExist );

        PY_THROW_ERROR_IF( true, PyExc_KeyError, strings::traderDoesNotExist );
    }

    return traderExist;
}


} /* namespace pyxchange */



/* EOF */

