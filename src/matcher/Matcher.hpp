/**0
 * @brief This module implements simulator of exchange
 * @file Matcher.hpp
 * 
 */

#ifndef MATCHER_HPP
#define MATCHER_HPP

#include "PyXchange.hpp"
#include "logger/Logger.hpp"


namespace pyxchange
{


class Matcher: public std::enable_shared_from_this<Matcher>
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
    static void         handleMessage( const CLIENT& client, const DATA& data );

    static void         handleCreateOrder( const TraderPtr& trader, const boost::python::dict& decoded );
    static void         handleCancelOrder( const TraderPtr& trader, const boost::python::dict& decoded );
    static void         handleCancelAll(   const TraderPtr& trader );

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


/**
 * @brief FIXME
 *
 */
template<typename CLIENT, typename DATA>
inline void Matcher::handleMessage( const CLIENT& client, const DATA& data )
{
    client->matcher->handleMessageImpl( client, data );
}


} /* namespace pyxchange */


#endif /* MATCHER_HPP */


/* EOF */

