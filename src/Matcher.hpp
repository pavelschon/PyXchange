/**0
 * @brief This module implements simulator of exchange
 * @file Matcher.hpp
 * 
 */

#ifndef MATCHER
#define MATCHER

#include "PyXchangeFwd.hpp"
#include "logger/Logger.hpp"


namespace pyxchange
{


class Matcher
{
public:
                        Matcher();
    explicit            Matcher( const boost::python::object& logger_ );
                        Matcher( const Matcher& ) = delete;
    Matcher&            operator=( const Matcher& ) = delete;

    /* public Matcher API (see MatcherApi.cpp */

    TraderPtr           getTrader( const std::string& name, const boost::python::object& transport );
    void                removeTrader( const TraderPtr& trader );

    ClientPtr           getClient( const std::string& name, const boost::python::object& transport );
    void                removeClient( const ClientPtr& client );

    template<typename CLIENT, typename DATA>
    static void         handleMessage( const CLIENT& client, const MatcherPtr& matcher, const DATA& data );

    static void         handleCreateOrder( const TraderPtr& trader, const MatcherPtr& matcher,
                                           const boost::python::dict& decoded );

    static void         handleCancelOrder( const TraderPtr& trader, const MatcherPtr& matcher,
                                           const boost::python::dict& decoded );

private:
    void                handleMessageImpl( const TraderPtr& trader, const std::string& data );
    void                handleMessageImpl( const TraderPtr& trader, const boost::python::dict& decoded );

    TraderSet::const_iterator findClient( const TraderPtr& trader ) const;
    ClientSet::const_iterator findClient( const ClientPtr& client ) const;

    static std::wstring extractMessage( const boost::python::dict& decoded );

    const Logger        logger;
    const TraderSetPtr  traders;
    const ClientSetPtr  clients;
    const OrderBookPtr  orderbook;
};


} /* namespace pyxchange */


#endif /* MATCHER */


/* EOF */

