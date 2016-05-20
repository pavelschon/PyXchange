/**
 * @brief This module implements simulator of exchange
 * @file MatchingEngine.hpp
 * 
 */

#ifndef MATCHINENGINE
#define MATCHINGENGINE

#include "PyXchangeFwd.hpp"
#include "OrderBook.hpp"


namespace pyxchange
{


class MatchingEngine
{

public:
                                            MatchingEngine();

    static void                             addTrader(
                                                const MatchingEnginePtr& matcher,
                                                const TraderPtr& trader
                                            );

    static void                             addClient(
                                                const MatchingEnginePtr& matcher,
                                                const ClientPtr& client
                                            );

    static const std::string                name;

private:
    OrderBook                               orderbook;

    TraderVector                            traders;
    ClientVector                            clients;
};


} /* namespace pyxchange */


#endif /* MATCHINENGINE */


/* EOF */


