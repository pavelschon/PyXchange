/**
 * @brief This module implements simulator of exchange
 * @file MDClient.cpp
 *
 */


#include "Client.hpp"
#include "Utils.hpp"


namespace pyxchange
{


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


} /* namespace pyxchange */



/* EOF */


