/**
 * @brief This module implements simulator of exchange
 * @file MDClient.cpp
 *
 */


#include "Client.hpp"
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
Client::Client( const boost::python::object& write_ ):
      write( write_ )
{

}


/**
 * @brief FIXME
 *
 */
void Client::writeString( const std::string& data )
{
    write( data );
}


/**
 * @brief FIXME
 *
 */
void Client::writeData( const boost::python::object& data )
{
    write( json::dumps<const std::string>( data ) );
}


/**
 * @brief FIXME
 *
 */
void Client::writeAll( const MatcherConstPtr& matcher, const boost::python::object& data )
{
    for( const auto& client : matcher->clients )
    {
        const auto& client_ = client.lock(); // from weak_ptr to shared_ptr

        if( client_ )
        {
            client_->writeData( data );
        }
    }
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

        PyErr_SetString( PyExc_ValueError, strings::clientAlreadyAdded.c_str() );

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

        PyErr_SetString( PyExc_KeyError, strings::clientDoesNotExist.c_str() );

        py::throw_error_already_set();
    }
}


/**
 * @brief FIXME
 *
 */
void Client::notifyError( const std::string& text )
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
void Client::notifyAllOrderBook( const MatcherConstPtr& matcher, const price_t priceLevel,
                                 const side_t side_, const quantity_t quantity )
{
    boost::python::dict response;

    response[ keys::message  ] = message::orderBook;
    response[ keys::side     ] = side::toBidAsk( side_ );
    response[ keys::price    ] = priceLevel;
    response[ keys::quantity ] = quantity;

    Client::writeAll( matcher, response );
}



} /* namespace pyxchange */



/* EOF */


