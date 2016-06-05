/**
 * @brief This module implements simulator of exchange
 * @file Matcher.hpp
 * 
 */

#ifndef MATCHER
#define MATCHER

#include "PyXchangeFwd.hpp"
//#include "OrderBook.hpp"
#include "Logger.hpp"


namespace pyxchange
{


class Matcher
{
public:
                        Matcher();
    explicit            Matcher( const boost::python::object& logger_ );
                        Matcher( const Matcher& ) = delete;
    Matcher&            operator=( const Matcher& ) = delete;

    TraderPtr           getTrader( const std::string& name, const boost::python::object& transport );
    void                removeTrader( const TraderPtr& trader );

    ClientPtr           getClient( const std::string& name, const boost::python::object& transport );
    void                removeClient( const ClientPtr& client );

    static void         handleTraderMessageStr( const TraderPtr& trader, const MatcherPtr& matcher, const std::string& data );
    static void         handleTraderMessageDict( const TraderPtr& trader, const MatcherPtr& matcher,  const boost::python::dict& decoded );

private:
    void                handleMessageStr( const TraderPtr& trader, const std::string& data );
    void                handleMessageDict( const TraderPtr& trader, const boost::python::dict& decoded );

    static std::wstring extractMessage( const boost::python::dict& decoded );

    const Logger        logger;
    const TraderSetPtr  traders;
    const ClientSetPtr  clients;
    const OrderBookPtr  orderbook;
};


} /* namespace pyxchange */


#endif /* MATCHER */


/* EOF */

