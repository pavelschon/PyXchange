/**
 * @brief This module implements simulator of exchange
 * @file Trader.cpp
 *
 */


#include "Trader.hpp"
#include "Constants.hpp"


namespace pyxchange
{

namespace py = boost::python;


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
void Trader::notifyOrderAlreadyExist( const orderId_t orderId )
{
    py::dict response;

    response[ keys::message ] = message::executionReport;
    response[ keys::report  ] = report::err;
    response[ keys::text    ] = boost::format( format::f0::orderAlreadyExist ).str();
    response[ keys::orderId ] = orderId;

    // send response
    writeData( response );
}



/**
 * @brief FIXME
 *
 */
void Trader::notifyOrderDoesNotExist( const orderId_t orderId )
{
    py::dict response;

    response[ keys::message ] = message::executionReport;
    response[ keys::report  ] = report::err;
    response[ keys::text    ] = boost::format( format::f0::orderDoesNotExist ).str();
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
void Trader::notifySelfMatch( const orderId_t orderId, const orderId_t oppOrderId )
{
    py::dict response;

    response[ keys::message ] = message::executionReport;
    response[ keys::report  ] = report::err;
    response[ keys::text    ] = boost::format( format::f0::selfMatch ).str();
    response[ keys::orderId ] = orderId;

    // send response
    writeData( response );
}


} /* namespace pyxchange */



/* EOF */

