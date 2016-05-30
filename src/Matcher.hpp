/**
 * @brief This module implements simulator of exchange
 * @file Matcher.hpp
 * 
 */

#ifndef MATCHER
#define MATCHER

#include "PyXchangeFwd.hpp"
#include "Client.hpp"
#include "Trader.hpp"


namespace pyxchange
{


class Matcher
{
private:
    const OrderBookPtr                      orderbook;

    TraderSet                               traders;
    ClientSet                               clients;

public:
                                            Matcher();
                                            Matcher( const Matcher& ) = delete;
                                            Matcher& operator=( const Matcher& ) = delete;

    static void                             handleMessageStr(
                                                const MatcherPtr& matcher,
                                                const TraderPtr& trader,
                                                const std::string& data
                                            );

    static void                             handleMessageDict(
                                                const MatcherPtr& matcher,
                                                const TraderPtr& trader,
                                                const boost::python::dict& decoded
                                            );

private:
    static void                             handleMessageImpl(
                                                const MatcherPtr& matcher,
                                                const TraderPtr& trader,
                                                const boost::python::dict& decoded
                                            );

    static size_t                           cancelAllOrders(
                                                const MatcherPtr& matcher,
                                                const TraderPtr& trader
                                            );

    friend void                             Client::addClient(
                                                const MatcherPtr& matcher,
                                                const ClientPtr& client
                                            );

    friend void                             Client::removeClient(
                                                const MatcherPtr& matcher,
                                                const ClientPtr& client
                                            );

    friend void                             Client::writeAll(
                                                const MatcherConstPtr& matcher,
                                                const boost::python::object& data
                                            );

    friend void                             Trader::addTrader(
                                                const MatcherPtr& matcher,
                                                const TraderPtr& trader
                                            );

    friend void                             Trader::removeTrader(
                                                const MatcherPtr& matcher,
                                                const TraderPtr& trader
                                            );

    friend bool                             Trader::checkRegistered(
                                                const MatcherConstPtr& matcher,
                                                const TraderPtr& trader
                                            );
};


} /* namespace pyxchange */


#endif /* MATCHER */


/* EOF */

