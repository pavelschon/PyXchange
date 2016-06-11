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


class Matcher
{
public:
                        Matcher();
    explicit            Matcher( const boost::python::object& logger_ );
                        Matcher( const Matcher& ) = delete;
    Matcher&            operator=( const Matcher& ) = delete;

    static ClientPtr    makeClient( const MatcherPtr& matcher, const std::string& name,
                                    const boost::python::object& transport );

    template<typename CLIENT, typename DATA>
    static void         handleMessage( const CLIENT& client, const DATA& data );

    static void         handleCreateOrder( const TraderPtr& trader, const boost::python::dict& decoded );
    static void         handleCancelOrder( const TraderPtr& trader, const boost::python::dict& decoded );
    static void         handleCancelAll(   const TraderPtr& trader );

private:
    template<typename CLIENT>
    void                handleMessageImpl( const CLIENT& client, const std::string& data );

    template<typename CLIENT>
    void                handleMessageImpl( const CLIENT& trader, const boost::python::dict& decoded );

    void                handleMessageImpl( const TraderPtr& trader, const boost::python::dict& decoded, const std::wstring message_ );
    void                handleMessageImpl( const ClientPtr& client, const boost::python::dict& decoded, const std::wstring message_ );

    static std::wstring extractMessage( const boost::python::dict& decoded );

    const Logger        logger;
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

