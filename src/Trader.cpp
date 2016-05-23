/**
 * @brief This module implements simulator of exchange
 * @file Trader.cpp
 *
 */


#include "Trader.hpp"
#include "Order.hpp"
#include "Utils.hpp"


namespace pyxchange
{


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
void Trader::writeString( const char* const data )
{
    write( data );
}


/**
 * @brief FIXME
 *
 */
void Trader::writeData( const boost::python::object& data )
{
    write( json_dumps<const char* const>( data ) );
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
void Trader::notifyError( const char* const text  )
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


