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
void Client::notifyOrderBook( const ClientSet& clients, const price_t priceLevel,
                              const side_t side_, const quantity_t quantity )
{
    py::dict response;

    response[ keys::type     ] = message::orderBook;
    response[ keys::side     ] = side::toBidAsk( side_ );
    response[ keys::price    ] = priceLevel;
    response[ keys::quantity ] = quantity;

    for( const auto& client : clients )
    {
        const auto& client_ = client.lock(); // from weak_ptr to shared_ptr

        if( client_ )
        {
            client_->writeData( response );
        }
    }
}


} /* namespace pyxchange */



/* EOF */


