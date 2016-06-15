/**
 * @brief   Base class implementing shared functionality of Trader and Client
 * @file    BaseClient.cpp
 *
 */


#include "client/BaseClient.hpp"
#include "utils/Exception.hpp"
#include "utils/Constants.hpp"


namespace pyxchange
{

namespace py = boost::python;


namespace attr
{

const char* const disconnect    = "disconnect";
const char* const handleMessage = "handleMessage";

}


/**
 * @brief   Constructor
 * @param   matcher_ related to the client
 * @param   name_ of the client
 * @param   transport_ object with methods write(str)/writeData(obj) and loseConnection()
 *
 */
BaseClient::BaseClient( const MatcherPtr& matcher_, const std::string& name_, const py::object& transport_ ):
      matcher{ matcher_ }
    , name{ name_ }
    , transport{ transport_ }
{
    if( !( hasattr( transport, attr::handleMessage ) ) )
    {
        pyexc::raise( PyExc_AttributeError, format::f0::errNoHandleMessage );
    }

    if( !( hasattr( transport, attr::disconnect ) ) )
    {
        pyexc::raise( PyExc_AttributeError, format::f0::errNoDisconnect );
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
 * @brief   Dump python structure into JSON and write it into 'transport' object
 * @param   data python structure
 *
 */
void BaseClient::writeData( const py::object& data )
{
    transport.attr( attr::handleMessage )( data );
}


/**
 * @brief   Disconnect the client by calling transport.loseConnection()
 * @return  void
 *
 */
void BaseClient::disconnect( void )
{
    if( hasattr( transport, attr::disconnect ) )
    {
        transport.attr( attr::disconnect )();
    }
}


} /* namespace pyxchange */



/* EOF */

