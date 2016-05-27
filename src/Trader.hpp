/**
 * @brief This module implements simulator of exchange
 * @file OrderBook.hpp
 *
 */

#ifndef TRADER
#define TRADER

#include "PyXchangeFwd.hpp"
#include "Order.hpp"
#include "Utils.hpp"


namespace pyxchange
{


class Trader
{

public:
    explicit                                Trader( const boost::python::object& write_ );

    void                                    writeString( const std::string& data );
    void                                    writeData( const boost::python::object& data );

    void                                    notifyError( const std::string& text );

    void                                    error( PyObject* const err, const std::string& text );

    void                                    notifyCreateOrderSuccess( const orderId_t orderId );
    void                                    notifyCreateOrderError( const orderId_t orderId, const std::string& text );

    void                                    notifyCancelOrderSuccess( const orderId_t orderId );
    void                                    notifyCancelOrderError( const orderId_t orderId, const std::string& text );

    size_t                                  cancelOrder( const orderId_t orderId );

    template<typename... Params>
    static OrderCreateResult                createOrder( const TraderPtr& trader, Params... params );

    static void                             addTrader( const MatcherPtr& matcher, const TraderPtr& trader );
    static void                             removeTrader( const MatcherPtr& matcher, const TraderPtr& trader );
    static bool                             checkRegistered( const MatcherConstPtr& matcher, const TraderPtr& trader );

private:
    const boost::python::object             write;

    OrderMap                                orders;
};


/**
 * @brief FIXME
 *
 */
inline void Trader::error( PyObject* const err, const std::string& text )
{
    boost::python::dict response;

    response[ keys::message ] = message::executionReport;
    response[ keys::report  ] = report::err;
    response[ keys::text    ] = text;

    // send response
    writeData( response );

    PyErr_SetString( err, text.c_str() );

    boost::python::throw_error_already_set();
}



} /* namespace pyxchange */


#endif /* TRADER */


/* EOF */

