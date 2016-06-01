/**
 * @brief This module implements simulator of exchange
 * @file BaseClient.cpp
 *
 */


#include "BaseClient.hpp"
#include "Json.hpp"


namespace pyxchange
{

namespace py = boost::python;


namespace attr
{
    const char* const loseConnection    = "loseConnection";
    const char* const write             = "write";
}


/**
 * @brief Constructor
 *
 */
BaseClient::BaseClient( const std::string& name_, const boost::python::object& transport_ ):
      name( name_ )
    , transport( transport_ )
{

}


/**
 * @brief Destructor
 *
 */
BaseClient::~BaseClient()
{

}


/**
 * @brief FIXME
 *
 */
std::string BaseClient::getName( void ) const
{
    return name;
}


/**
 * @brief FIXME
 *
 */
void BaseClient::writeString( const std::string& data )
{
    transport.attr( attr::write )( data );
    //transport.attr( attr::write )( '\n' );
}


/**
 * @brief FIXME
 *
 */
void BaseClient::writeData( const boost::python::object& data )
{
    transport.attr( attr::write )( json::dumps<const std::string>( data ) );
//     transport.attr( attr::write )( '\n' );
}


/**
 * @brief FIXME
 *
 */
void BaseClient::disconnect( void )
{
    transport.attr( attr::loseConnection )();
}


} /* namespace pyxchange */



/* EOF */

