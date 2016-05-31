/**
 * @brief This module implements simulator of exchange
 * @file Matcher.hpp
 * 
 */

#ifndef MATCHER
#define MATCHER

#include "PyXchangeFwd.hpp"
#include "Client.hpp"


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

    void                                    removeClient( const ClientPtr& client );
    void                                    removeTrader( const TraderPtr& trader );

    ClientPtr                               getClient(
                                                const std::string& name,
                                                const boost::python::object& transport
                                            );

    TraderPtr                               getTrader(
                                                const std::string& name,
                                                const boost::python::object& transport
                                            );

    void                                    notifyAllClients(
                                                const boost::python::object& data
                                            ) const;

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

    void                                    log(
                                                const std::string& level,
                                                const boost::format& message
                                            ) const;
};


} /* namespace pyxchange */


#endif /* MATCHER */


/* EOF */

