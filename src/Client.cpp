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


} /* namespace pyxchange */



/* EOF */


