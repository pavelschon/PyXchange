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

    void                                    addClient( const ClientPtr& client );
    void                                    removeClient( const ClientPtr& client );

    void                                    addTrader( const TraderPtr& trader );
    void                                    removeTrader( const TraderPtr& trader );

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
    bool                                    checkRegistered( const TraderPtr& trader ) const;

    void                                    handleMessageImpl(
                                                const TraderPtr& trader,
                                                const boost::python::dict& decoded
                                            );

    friend void                             Client::writeAll(
                                                const MatcherConstPtr& matcher,
                                                const boost::python::object& data
                                            );
};


} /* namespace pyxchange */


#endif /* MATCHER */


/* EOF */

