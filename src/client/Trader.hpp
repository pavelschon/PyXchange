/**
 * @brief   Implementaton of Trader
 * @file    Trader.hpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */

#ifndef TRADER_HPP
#define TRADER_HPP

#include "PyXchange.hpp"
#include "client/BaseClient.hpp"


namespace pyxchange
{


class Trader: public BaseClient
{
public:
    using BaseClient::BaseClient;

                Trader( const Trader& ) = delete;
    Trader&     operator=( const Trader& ) = delete;

    void        notifyPong();
    void        notifyError( const std::string& text );

    void        notifyCancelOrderSuccess( const orderId_t orderId, const quantity_t quantity );
    void        notifyCreateOrderSuccess( const orderId_t orderId, const quantity_t quantity );

    void        notifyTrade( const orderId_t orderId, const price_t price,
                             const quantity_t quantity );
};


} /* namespace pyxchange */


#endif /* TRADER_HPP */


/* EOF */

