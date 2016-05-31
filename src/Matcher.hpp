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


class Matcher: public std::enable_shared_from_this<Matcher>
{
private:
    const OrderBookPtr                      orderbook;
    const boost::python::object             logger;

    TraderSet                               traders;
    ClientSet                               clients;

public:
                                            Matcher();
    explicit                                Matcher( const boost::python::object& logger_ );
                                            Matcher( const Matcher& ) = delete;
                                            Matcher& operator=( const Matcher& ) = delete;

    void                                    handleMessageStr(
                                                const TraderPtr& trader,
                                                const std::string& data
                                            );

    void                                    handleMessageDict(
                                                const TraderPtr& trader,
                                                const boost::python::dict& decoded
                                            );

    void                                    log(
                                                const std::string& level,
                                                const std::string& message
                                            ) const;

private:
    void                                    handleMessageImpl(
                                                const TraderPtr& trader,
                                                const boost::python::dict& decoded
                                            );

    size_t                                  cancelAllOrders( const TraderPtr& trader );

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

