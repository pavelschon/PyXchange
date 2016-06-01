/**
 * @brief This module implements simulator of exchange
 * @file Trader.cpp
 *
 */


#include "Trader.hpp"


namespace pyxchange
{

namespace py = boost::python;


namespace report
{

const std::string new_   = "NEW";
const std::string cancel = "CANCELED";
const std::string fill   = "FILL";
const std::string err    = "ERROR";

} /* namespace report */


namespace message
{

const std::string executionReport    = "executionReport";

} /* namespace message */


namespace format
{

const boost::format orderDoesNotExist( "order does not exists" );
const boost::format orderAlreadyExist( "order already exists" );
const boost::format selfMatch( "self-match rejected" );

} /* namespace format */


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
    response[ keys::text    ] = boost::format( format::orderAlreadyExist ).str();
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
    response[ keys::text    ] = boost::format( format::orderDoesNotExist ).str();
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
    response[ keys::text    ] = boost::format( format::selfMatch ).str();
    response[ keys::orderId ] = orderId;

    // send response
    writeData( response );
}


} /* namespace pyxchange */



/* EOF */

