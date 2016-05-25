/**
 * @brief This module implements simulator of exchange
 * @file OrderBook.hpp
 *
 */

#ifndef TRADER
#define TRADER

#include "PyXchangeFwd.hpp"
#include "Order.hpp"

#include <boost/python/object.hpp>


namespace pyxchange
{


class Trader
{

public:
    explicit                                Trader( const boost::python::object& write_ );

    void                                    writeString( const char* const data );
    void                                    writeData( const boost::python::object& data );

    size_t                                  cancelOrder( const orderId_t orderId );

    template<typename... Params>
    static OrderCreateResult                createOrder( const TraderPtr& trader, Params... params );

    static void                             addTrader( const MatcherPtr& matcher, const TraderPtr& trader );
    static void                             removeTrader( const MatcherPtr& matcher, const TraderPtr& trader );
    static bool                             checkRegistered( const MatcherPtr& matcher, const TraderPtr& trader );

    void                                    notifyError( const char* const text );

    static constexpr const char* const      name = "Trader";

private:
    const boost::python::object             write;

    OrderMap                                orders;
};


} /* namespace pyxchange */


#endif /* TRADER */


/* EOF */


