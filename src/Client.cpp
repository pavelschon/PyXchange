/**
 * @brief This module implements simulator of exchange
 * @file MDClient.cpp
 *
 */


#include "Client.hpp"


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
void Client::operator()( const char* const data )
{
    write( data );
}


} /* namespace pyxchange */



/* EOF */


