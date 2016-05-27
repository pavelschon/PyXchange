/**
 * @brief This module implements simulator of exchange
 * @file Trader.cpp
 *
 */


#include "Trader.hpp"
#include "Matcher.hpp"
#include "Json.hpp"
#include "Utils.hpp"


namespace pyxchange
{

namespace py = boost::python;


/**
 * @brief Constructor
 *
 */
Trader::Trader( const boost::python::object& write_ ):
      write( write_ )
{

}


/**
 * @brief FIXME
 *
 */
void Trader::writeString( const std::string& data )
{
    write( data );
}


/**
 * @brief FIXME
 *
 */
void Trader::writeData( const boost::python::object& data )
{
    write( json::dumps<const std::string>( data ) );
}


/**
 * @brief FIXME
 *
 */
size_t Trader::cancelOrder( const orderId_t orderId )
{
    return orders.erase( orderId );
}


/**
 * @brief FIXME
 *
 */
void Trader::addTrader( const MatcherPtr& matcher, const TraderPtr& trader )
{
    if( ! matcher->traders.insert( trader ).second )
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
void Trader::removeTrader( const MatcherPtr& matcher, const TraderPtr& trader )
{
    const auto& it = matcher->traders.find( trader );

    if( it != matcher->traders.cend() )
    {
        matcher->traders.erase( it );
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
bool Trader::checkRegistered( const MatcherConstPtr& matcher, const TraderPtr& trader )
{
    const auto traderExist = matcher->traders.count( trader ) > 0;

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

