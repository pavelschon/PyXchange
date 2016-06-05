/**
 * @brief   Market-data Client implementation
 * @file    Client.cpp
 *
 */


#include "Client.hpp"
#include "Constants.hpp"
#include "Side.hpp"


namespace pyxchange
{

namespace py = boost::python;


/**
 * @brief   Write 'orderbook' message to this client
 * @param   price_t     price priceLevel
 * @param   side_t      side
 * @param   quantity_t  quantity
 * @return  void
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
 * @brief   Write 'orderbook' message to all clients
 * @param   ClientSetConstPtr set of clients
 * @param   price_t     price priceLevel
 * @param   side_t      side
 * @param   quantity_t  quantity
 * @return  void
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
 * @brief   Write 'trade' message to this client
 * @param   prio_t      time of match event
 * @param   price_t     price priceLevel
 * @param   quantity_t  quantity
 * @return  void
 *
 */
void Client::notifyTrade( const ClientSetConstPtr& clients, const prio_t time,
                          const price_t price, const quantity_t quantity )
{
    const auto toSeconds = [time]() -> float {
        return std::chrono::time_point_cast<
            std::chrono::microseconds>( time ).time_since_epoch().count() / 1e6f; };

    py::dict response;

    response[ keys::type     ] = message::trade;
    response[ keys::time     ] = toSeconds();
    response[ keys::price    ] = price;
    response[ keys::quantity ] = quantity;

    writeAll( clients, response );
}


/**
 * @brief   Distribute message across all clients
 * @param   ClientSetConstPtr set of clients
 * @param   py::object data to be written
 * @return  void
 *
 */
void Client::writeAll( const ClientSetConstPtr& clients, const py::object& data )
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

