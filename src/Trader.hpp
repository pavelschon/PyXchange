/**
 * @brief This module implements simulator of exchange
 * @file OrderBook.hpp
 *
 */

#ifndef TRADER
#define TRADER

#include "PyXchangeFwd.hpp"


namespace pyxchange
{


class Trader
{
private:
    const boost::python::object             write; // callback

public:
    explicit                                Trader( const boost::python::object& write_ );

    void                                    writeString( const std::string& data );
    void                                    writeData( const boost::python::object& data );

    void                                    notifyError( const std::string& text );

    void                                    notifyCreateOrderSuccess( const orderId_t orderId );
    void                                    notifyCancelOrderSuccess( const orderId_t orderId );

    void                                    notifyCreateOrderError(
                                                const orderId_t orderId,
                                                const std::string& text
                                            );

    void                                    notifyCancelOrderError(
                                                const orderId_t orderId,
                                                const std::string& text
                                            );

    static void                             addTrader(
                                                const MatcherPtr& matcher,
                                                const TraderPtr& trader
                                            );

    static void                             removeTrader(
                                                const MatcherPtr& matcher,
                                                const TraderPtr& trader
                                            );

    static bool                             checkRegistered(
                                                const MatcherConstPtr& matcher,
                                                const TraderPtr& trader
                                            );
};


} /* namespace pyxchange */


#endif /* TRADER */


/* EOF */

