/**
 * @brief   Implementaton of Trader
 * @file    Trader.cpp
 *
 */


#include "client/Trader.hpp"
#include "utils/Constants.hpp"


namespace pyxchange
{

namespace py = boost::python;


/**
 * @brief   Pong notification
 *
 */
void Trader::notifyPong( void )
{
    py::dict response;

    response[ keys::message ] = message::pong;

    writeData( response );
}


/**
 * @brief   Write error message to Trader
 * @param   text of the message
 *
 */
void Trader::notifyError( const std::string& text )
{
    boost::python::dict response;

    response[ keys::message ] = message::error;
    response[ keys::text    ] = text;

    // send response
    writeData( response );
}


/**
 * @brief Notify Trader about created order
 * @param orderId of new order (for verification)
 * @param quantity of new order (for verification)
 *
 */
void Trader::notifyCreateOrderSuccess( const orderId_t orderId, const quantity_t quantity )
{
    py::dict response;

    response[ keys::message  ] = message::executionReport;
    response[ keys::report   ] = report::new_;
    response[ keys::orderId  ] = orderId;
    response[ keys::quantity ] = quantity;

    // send response
    writeData( response );
}


/**
 * @brief Notify Trader about canceled order
 * @param quantity of canceled order (for verification)
 *
 */
void Trader::notifyCancelOrderSuccess( const orderId_t orderId, const quantity_t quantity )
{
    py::dict response;

    response[ keys::message  ] = message::executionReport;
    response[ keys::report   ] = report::cancel;
    response[ keys::orderId  ] = orderId;
    response[ keys::quantity ] = quantity;

    // send response
    writeData( response );
}


/**
 * @brief Notify Trader about match event
 * @param   orderId of matched order
 * @param   price of match event
 * @param   quantity of match event
 *
 */
void Trader::notifyTrade( const orderId_t orderId, const price_t price, const quantity_t quantity )
{
    py::dict response;

    response[ keys::message  ] = message::executionReport;
    response[ keys::report   ] = report::fill;
    response[ keys::orderId  ] = orderId;
    response[ keys::price    ] = price;
    response[ keys::quantity ] = quantity;

    // send response
    writeData( response );
}


} /* namespace pyxchange */


/* EOF */

