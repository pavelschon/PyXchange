/**
 * @brief   Market-data Client implementation
 * @file    Client.cpp
 *
 */


#include "client/Client.hpp"
#include "utils/Constants.hpp"
#include "utils/Side.hpp"


namespace pyxchange
{

namespace py = boost::python;


/**
 * @brief   Write 'orderbook' summary message to this client
 * @param   price priceLevel of the summary
 * @param   side of the the summary
 * @param   quantity on the price level
 *
 */
void Client::notifyOrderBook( const price_t priceLevel, const side_t side_, const quantity_t quantity )
{
    py::dict response;

    response[ keys::type     ] = message::orderBook;
    response[ keys::side     ] = side::toBidAsk( side_ );
    response[ keys::price    ] = priceLevel;
    response[ keys::quantity ] = quantity;

    handleMessage( response );
}


/**
 * @brief   Write 'orderbook' message to all clients
 * @param   clients set of clients
 * @param   price priceLevel of the summary
 * @param   side of the the summary
 * @param   quantity on the price level
 *
 */
void Client::notifyOrderBook( const ClientVectorConstPtr& clients, const price_t priceLevel,
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
 * @brief   Write 'trade' message to the client
 * @param   time of match event
 * @param   price of match event
 * @param   quantity of match event
 *
 */
void Client::notifyTrade( const ClientVectorConstPtr& clients, const prio_t time,
                          const price_t price, const quantity_t quantity )
{
    py::dict response;

    response[ keys::type     ] = message::trade;
    response[ keys::time     ] = time.time_since_epoch().count() / 1.0e9;
    response[ keys::price    ] = price;
    response[ keys::quantity ] = quantity;

    writeAll( clients, response );
}


/**
 * @brief   Distribute message to all clients. Clients are notified in random order.
 * @param   client set of clients
 * @param   data to be written
 *
 */
void Client::writeAll( const ClientVectorConstPtr& clients, const py::object& data )
{
    ClientVector clients_{ *clients };

    std::random_shuffle( clients_.begin(), clients_.end() );

    for( const auto& client : clients_ )
    {
        const auto& client_ = client.lock(); // from weak_ptr to shared_ptr

        if( client_ )
        {
            client_->handleMessage( data );
        }
    }
}


} /* namespace pyxchange */


/* EOF */

