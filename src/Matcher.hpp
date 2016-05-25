/**
 * @brief This module implements simulator of exchange
 * @file Matcher.hpp
 * 
 */

#ifndef MATCHER
#define MATCHER

#include "PyXchangeFwd.hpp"
#include "OrderBook.hpp"
#include "Client.hpp"
#include "Trader.hpp"


namespace pyxchange
{


class Matcher
{

public:
                                            Matcher();

    friend void                             Client::addClient( const MatcherPtr& matcher, const ClientPtr& client );
    friend void                             Client::removeClient( const MatcherPtr& matcher, const ClientPtr& client );

    friend void                             Trader::addTrader( const MatcherPtr& matcher, const TraderPtr& trader );
    friend void                             Trader::removeTrader( const MatcherPtr& matcher, const TraderPtr& trader );

    static void                             handleMessageStr(  const MatcherPtr& matcher, const TraderPtr& trader, const char* const data );
    static void                             handleMessageDict( const MatcherPtr& matcher, const TraderPtr& trader, const boost::python::dict& decoded );

    static constexpr const char* const      name = "Matcher";

private:
    friend bool                             Trader::checkRegistered( const MatcherPtr& matcher, const TraderPtr& trader );

    static void                             handleMessageImpl( const MatcherPtr& matcher, const TraderPtr& trader, const boost::python::dict& decoded );

    TraderSet                               traders;
    ClientSet                               clients;

    OrderBook                               orderbook;
};


} /* namespace pyxchange */


#endif /* MATCHER */


/* EOF */

