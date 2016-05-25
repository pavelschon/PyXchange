/**
 * @brief This module implements simulator of exchange
 * @file OrderBook.hpp
 *
 */

#ifndef TRADER
#define TRADER

#include "PyXchangeFwd.hpp"
#include "Order.hpp"


namespace pyxchange
{


class Trader
{

public:
    explicit                                Trader( const boost::python::object& write_ );

    void                                    writeString( const char* const data );
    void                                    writeData( const boost::python::object& data );

    void                                    notifyError( const char* const text );

    void                                    notifyCreateOrderSuccess( const orderId_t orderId );
    void                                    notifyCreateOrderError( const orderId_t orderId );

    void                                    notifyCancelOrderSuccess( const orderId_t orderId );
    void                                    notifyCancelOrderError( const orderId_t orderId );

    size_t                                  cancelOrder( const orderId_t orderId );

    template<typename... Params>
    static OrderCreateResult                createOrder( const TraderPtr& trader, Params... params );

    static void                             addTrader( const MatcherPtr& matcher, const TraderPtr& trader );
    static void                             removeTrader( const MatcherPtr& matcher, const TraderPtr& trader );
    static bool                             checkRegistered( const MatcherPtr& matcher, const TraderPtr& trader );

private:
    const boost::python::object             write;

    OrderMap                                orders;
};


} /* namespace pyxchange */


#endif /* TRADER */


/* EOF */


