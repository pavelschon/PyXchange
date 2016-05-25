/**
 * @brief This module implements simulator of exchange
 * @file MDClient.cpp
 *
 */


#include "Client.hpp"
#include "Matcher.hpp"
#include "Utils.hpp"


namespace pyxchange
{

namespace py = boost::python;

/**
 * @brief Constructor
 *
 */
Client::Client( const boost::python::object& write_ ):
      write( write_ )
{

}


/**
 * @brief FIXME
 *
 */
void Client::writeString( const char* const data )
{
    write( data );
}


/**
 * @brief FIXME
 *
 */
void Client::writeData( const boost::python::object& data )
{
    write( json_dumps<const char* const>( data ) );
}


/**
 * @brief FIXME
 *
 */
void Client::notifyError( const char* const text  )
{
    boost::python::dict response;

    response[ keys::message ] = message::executionReport;
    response[ keys::report  ] = report::err;
    response[ keys::text    ] = text;

    // send response
    writeData( response );
}



/**
 * @brief FIXME
 *
 */
void Client::addClient( const MatcherPtr& matcher, const ClientPtr& client )
{
    if( ! matcher->clients.insert( client ).second )
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
void Client::removeClient( const MatcherPtr& matcher, const ClientPtr& client )
{
    const auto& it = matcher->clients.find( client );

    if( it != matcher->clients.cend() )
    {
        matcher->clients.erase( it );
    }
    else
    {
        client->notifyError( strings::clientDoesNotExist );

        PyErr_SetString( PyExc_KeyError, strings::clientDoesNotExist );

        py::throw_error_already_set();
    }
}


} /* namespace pyxchange */



/* EOF */


