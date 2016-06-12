/**
 * @brief This module implements simulator of exchange
 * @file Trader.cpp
 *
 */


#include "client/Trader.hpp"
#include "utils/Constants.hpp"


namespace pyxchange
{

namespace py = boost::python;


/**
 * @brief   FIXME
 * @return  void
 *
 */
void Trader::notifyPong( void )
{
    py::dict response;

    response[ keys::message ] = message::pong;

    writeData( response );
}


/**
 * @brief FIXME
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
 * @brief FIXME
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
 * @brief FIXME
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
 * @brief FIXME
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

