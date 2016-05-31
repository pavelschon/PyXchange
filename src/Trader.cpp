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
Trader::Trader( const std::string& name_, const boost::python::object& transport_ ):
      name( name_ )
    , transport( transport_ )
{

}


/**
 * @brief FIXME
 *
 */
std::string Trader::getName( void ) const
{
    return name;
}


/**
 * @brief FIXME
 *
 */
void Trader::writeString( const std::string& data )
{
    transport.attr( attr::write )( data );
    transport.attr( attr::write )( '\n' );
}


/**
 * @brief FIXME
 *
 */
void Trader::writeData( const boost::python::object& data )
{
    transport.attr( attr::write )( json::dumps<const std::string>( data ) );
    transport.attr( attr::write )( '\n' );
}


/**
 * @brief FIXME
 *
 */
void Trader::disconnect( void )
{
    transport.attr( attr::loseConnection )();
}


/**
 * @brief FIXME
 *
 */
void Trader::notifyError( const std::string& text )
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
void Trader::notifyCreateOrderSuccess( const orderId_t orderId )
{
    py::dict response;

    response[ keys::message ] = message::executionReport;
    response[ keys::report  ] = report::new_;
    response[ keys::orderId ] = orderId;

    // send response
    writeData( response );
}



/**
 * @brief FIXME
 *
 */
void Trader::notifyCreateOrderError( const orderId_t orderId, const std::string& text )
{
    py::dict response;

    response[ keys::message ] = message::executionReport;
    response[ keys::report  ] = report::err;
    response[ keys::text    ] = text;
    response[ keys::orderId ] = orderId;

    // send response
    writeData( response );
}


/**
 * @brief FIXME
 *
 */
void Trader::notifyCancelOrderSuccess( const orderId_t orderId )
{
    py::dict response;

    response[ keys::message ] = message::executionReport;
    response[ keys::report  ] = report::cancel;
    response[ keys::orderId ] = orderId;

    // send response
    writeData( response );
}


/**
 * @brief FIXME
 *
 */
void Trader::notifyCancelOrderError( const orderId_t orderId, const std::string& text )
{
    py::dict response;

    response[ keys::message ] = message::executionReport;
    response[ keys::report  ] = report::err;
    response[ keys::text    ] = text;
    response[ keys::orderId ] = orderId;

    // send response
    writeData( response );
}


} /* namespace pyxchange */



/* EOF */

