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

    static void         handleMessageJson( const TraderPtr& trader, const std::string& data );
    static void         handleMessageDict( const TraderPtr& trader, const boost::python::dict& decoded );
    static void         handleCreateOrder( const TraderPtr& trader, const boost::python::dict& decoded );
    static void         handleCancelOrder( const TraderPtr& trader, const boost::python::dict& decoded );
    static void         handleCancelAll(   const TraderPtr& trader );

private:
    void                handleMessageImpl( const TraderPtr& trader, const std::string& data );
    void                handleMessageImpl( const TraderPtr& trader, const boost::python::dict& decoded );
    void                handleMessageImpl( const TraderPtr& trader, const boost::python::dict& decoded,
                                           const std::wstring& message_ );

    static std::wstring extractMessage( const MessageVector& messages, const boost::python::dict& decoded );

    const Logger        logger;
    const ClientVectorPtr clients;
    const OrderBookPtr  orderbook;
};


} /* namespace pyxchange */


#endif /* MATCHER_HPP */


/* EOF */

