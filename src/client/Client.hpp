/**
 * @brief   Market-data Client implementation
 * @file    Client.hpp
 *
 */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "PyXchange.hpp"
#include "client/BaseClient.hpp"
#include "client/BaseClient.hpp"


namespace pyxchange
{


class Client: public BaseClient
{
public:
    using BaseClient::BaseClient;

                Client( const Client& ) = delete;
                Client& operator=( const Client& ) = delete;

    void        notifyPong( void );
    void        notifyError( const std::string& text );

    void        notifyOrderBook( const price_t priceLevel,
                                 const side_t side_, const quantity_t quantity );

    static void notifyOrderBook( const ClientVectorConstPtr& clients, const price_t priceLevel,
                                 const side_t side_, const quantity_t quantity );

    static void notifyTrade( const ClientVectorConstPtr& clients, const prio_t time,
                             const price_t price, const quantity_t quantity );

    static const MessageVector messages;

private:
    static void writeAll( const ClientVectorConstPtr& clients, const boost::python::object& data );
};


} /* namespace pyxchange */


#endif /* CLIENT_HPP */


/* EOF */

