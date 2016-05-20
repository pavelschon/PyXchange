/**
 * @brief This module implements simulator of exchange
 * @file Matcher.hpp
 * 
 */

#ifndef MATCHER
#define MATCHER

#include "PyXchangeFwd.hpp"
#include "OrderBook.hpp"


namespace pyxchange
{


class Matcher
{

public:
                                            Matcher();

    static void                             addTrader(
                                                const MatcherPtr& matcher,
                                                const TraderPtr& trader
                                            );

    static void                             addClient(
                                                const MatcherPtr& matcher,
                                                const ClientPtr& client
                                            );

    static const std::string                name;

private:
    OrderBook                               orderbook;

    TraderVector                            traders;
    ClientVector                            clients;
};


} /* namespace pyxchange */


#endif /* MATCHER */


/* EOF */


