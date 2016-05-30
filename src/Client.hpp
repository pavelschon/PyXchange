/**
 * @brief This module implements simulator of exchange
 * @file Client.hpp
 *
 */

#ifndef CLIENT
#define CLIENT

#include "PyXchangeFwd.hpp"


namespace pyxchange
{


class Client
{
private:
    const boost::python::object             write; // callback

public:
    explicit                                Client( const boost::python::object& write_ );
                                            Client( const Client& ) = delete;
                                            Client& operator=( const Client& ) = delete;

    void                                    writeString( const std::string& data );
    void                                    writeData( const boost::python::object& data );

    static void                             writeAll(
                                                const MatcherConstPtr& matcher,
                                                const boost::python::object& data
                                            );

    static void                             addClient(
                                                const MatcherPtr& matcher,
                                                const ClientPtr& client
                                            );

    static void                             removeClient(
                                                const MatcherPtr& matcher,
                                                const ClientPtr& client
                                            );

    void                                    notifyError( const std::string& text );

    void                                    notifyOrderBook(
                                                const price_t priceLevel,
                                                const side_t side_,
                                                const quantity_t quantity
                                            );

    static void                             notifyAllOrderBook(
                                                const MatcherConstPtr& matcher,
                                                const price_t priceLevel,
                                                const side_t side_,
                                                const quantity_t quantity
                                            );

};


} /* namespace pyxchange */


#endif /* CLIENT */


/* EOF */


