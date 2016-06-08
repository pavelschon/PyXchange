/**
 * @brief   Base class implementing shared functionality of Trader and Client
 * @file    BaseClient.cpp
 *
 */


#include "client/BaseClient.hpp"
#include "utils/Exception.hpp"
#include "utils/Constants.hpp"
#include "utils/Json.hpp"


namespace pyxchange
{

namespace py = boost::python;


/**
 * @brief   Constructor
 * @param   std::string name of the client
 * @param   py::object  transport
 *
 */
BaseClient::BaseClient( const std::string& name_, const py::object& transport_ ):
      name{ name_ }
    , transport{ transport_ }
{
    if( !( hasattr( transport, attr::writeData ) || hasattr( transport, attr::write ) ) )
    {
        pyexc::raise( PyExc_AttributeError, format::f0::errNoWriteAttr );
    }
}


/**
 * @brief   Destructor
 *
 */
BaseClient::~BaseClient()
{

}


/**
 * @brief   Get string representation of BaseClient
 * @return  string
 *
 */
std::string BaseClient::toString( void ) const
{
    return name;
}


/**
 * @brief   Dump py object into JSON and write it into 'transport' object
 * @param   py::object data to be written
 * @return  void
 *
 */
void BaseClient::writeData( const py::object& data )
{
    if( hasattr( transport, attr::writeData ) )
    {
        transport.attr( attr::writeData )( data );
    }
    else
    {
        transport.attr( attr::write )( json::dumps<const std::string>( data ) );
        transport.attr( attr::write )( '\n' );
    }
}


/**
 * @brief   Disconnect the client by calling transport.loseConnection()
 * @return  void
 *
 */
void BaseClient::disconnect( void )
{
    if( hasattr( transport, attr::loseConnection ) )
    {
        transport.attr( attr::loseConnection )();
    }
}


} /* namespace pyxchange */



/* EOF */

