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

    void        notifyOrderBook( const price_t priceLevel,
                                 const side_t side_, const quantity_t quantity );

    static void notifyOrderBook( const ClientSetConstPtr& clients, const price_t priceLevel,
                                 const side_t side_, const quantity_t quantity );

    static void notifyTrade( const ClientSetConstPtr& clients, const prio_t time,
                             const price_t price, const quantity_t quantity );

private:
    static void writeAll( const ClientSetConstPtr& clients,
                          const boost::python::object& data );
};


} /* namespace pyxchange */


#endif /* CLIENT */


/* EOF */


