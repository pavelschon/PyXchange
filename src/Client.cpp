/**
 * @brief This module implements simulator of exchange
 * @file MDClient.cpp
 *
 */


#include "Client.hpp"
#include "Utils.hpp"


namespace pyxchange
{

namespace py = boost::python;


namespace message
{

const std::string orderBook          = "orderbook";

} /* namespace message */


/**
 * @brief FIXME
 *
 */
void Client::notifyOrderBook( const price_t priceLevel, const side_t side_, const quantity_t quantity )
{
    boost::python::dict response;

    response[ keys::message  ] = message::orderBook;
    response[ keys::side     ] = side::toBidAsk( side_ );
    response[ keys::price    ] = priceLevel;
    response[ keys::quantity ] = quantity;

    writeData( response );
}



} /* namespace pyxchange */



/* EOF */


