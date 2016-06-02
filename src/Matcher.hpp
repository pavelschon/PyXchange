/**
 * @brief This module implements simulator of exchange
 * @file Matcher.hpp
 * 
 */

#ifndef MATCHER
#define MATCHER

#include "PyXchangeFwd.hpp"
#include "OrderBook.hpp"
#include "Logger.hpp"


namespace pyxchange
{


class Matcher
{
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

    TraderPtr                               getTrader(
                                                const std::string& name,
                                                const boost::python::object& transport
                                            );

    void                                    removeTrader(
                                                const TraderPtr& trader
                                            );

private:
    friend ClientPtr                        OrderBook::getClient(
                                                const MatcherPtr& matcher,
                                                const std::string& name,
                                                const boost::python::object& transport
                                            );

    friend void                             OrderBook::removeClient(
                                                const MatcherPtr& matcher,
                                                const ClientPtr& client
                                            );


    const Logger                            logger;

    OrderBook                               orderbook;

    TraderSet                               traders;
};


namespace log
{

    const std::string debug     = "debug";
    const std::string info      = "info";
    const std::string warning   = "warning";
    const std::string error     = "error";

} /* namespace log */


} /* namespace pyxchange */


#endif /* MATCHER */


/* EOF */

