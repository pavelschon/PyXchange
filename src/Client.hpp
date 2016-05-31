/**
 * @brief This module implements simulator of exchange
 * @file Client.hpp
 *
 */

#ifndef CLIENT
#define CLIENT

#include "PyXchangeFwd.hpp"
#include "BaseClient.hpp"


namespace pyxchange
{


class Client: public BaseClient
{
public:
    using BaseClient::BaseClient;

                                            Client( const Client& ) = delete;
                                            Client& operator=( const Client& ) = delete;

    static void                             writeAll(
                                                const MatcherConstPtr& matcher,
                                                const boost::python::object& data
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


