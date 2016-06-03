/**
 * @brief This module implements simulator of exchange
 * @file MDClient.cpp
 *
 */


#include "Client.hpp"
#include "Constants.hpp"
#include "Side.hpp"


namespace pyxchange
{

namespace py = boost::python;


/**
 * @brief FIXME
 *
 */
void Client::notifyOrderBook( const price_t priceLevel, const side_t side_, const quantity_t quantity )
{
    py::dict response;

    response[ keys::type     ] = message::orderBook;
    response[ keys::side     ] = side::toBidAsk( side_ );
    response[ keys::price    ] = priceLevel;
    response[ keys::quantity ] = quantity;

    writeData( response );
}


/**
 * @brief FIXME
 *
 */
void Client::notifyOrderBook( const ClientSetConstPtr& clients, const price_t priceLevel,
                              const side_t side_, const quantity_t quantity )
{
    py::dict response;

    response[ keys::type     ] = message::orderBook;
    response[ keys::side     ] = side::toBidAsk( side_ );
    response[ keys::price    ] = priceLevel;
    response[ keys::quantity ] = quantity;

    writeAll( clients, response );
}


/**
 * @brief FIXME
 *
 */
void Client::notifyTrade( const ClientSetConstPtr& clients, const prio_t time,
                          const price_t price, const quantity_t quantity )
{
    py::dict response;

    response[ keys::type     ] = message::trade;
    response[ keys::time     ] = 0;
    response[ keys::price    ] = price;
    response[ keys::quantity ] = quantity;

    writeAll( clients, response );
}


/**
 * @brief FIXME
 *
 */
void Client::writeAll( const ClientSetConstPtr& clients, const boost::python::object& data )
{
    for( const auto& client : *clients )
    {
        const auto& client_ = client.lock(); // from weak_ptr to shared_ptr

        if( client_ )
        {
            client_->writeData( data );
        }
    }
}



} /* namespace pyxchange */



/* EOF */


