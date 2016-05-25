/**
 * @brief This module implements simulator of exchange
 * @file Trader.cpp
 *
 */


#include "Trader.hpp"
#include "Matcher.hpp"
#include "Utils.hpp"


namespace pyxchange
{

namespace py = boost::python;


/**
    * @brief FIXME
    *
    */
void Trader::notifyError( const char* const text  )
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
void Trader::notifyCreateOrderError( const orderId_t orderId )
{
    py::dict response;

    response[ keys::message ] = message::executionReport;
    response[ keys::report  ] = report::err;
    response[ keys::text    ] = strings::orderAlreadyExist;
    response[ keys::orderId ] = orderId;

    // send response
    writeData( response );

    PyErr_SetString( PyExc_ValueError, strings::orderAlreadyExist );

    py::throw_error_already_set();
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
void Trader::notifyCancelOrderError( const orderId_t orderId )
{
    py::dict response;

    response[ keys::message ] = message::executionReport;
    response[ keys::report  ] = report::err;
    response[ keys::text    ] = strings::orderDoesNotExist;
    response[ keys::orderId ] = orderId;

    // send response
    writeData( response );

    PyErr_SetString( PyExc_ValueError, strings::orderDoesNotExist );

    py::throw_error_already_set();
}


} /* namespace pyxchange */


/* EOF */

