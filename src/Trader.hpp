/**
 * @brief This module implements simulator of exchange
 * @file Trader.hpp
 *
 */

#ifndef TRADER
#define TRADER

#include "PyXchangeFwd.hpp"
#include "BaseClient.hpp"


namespace pyxchange
{


class Trader: public BaseClient
{
public:
    using BaseClient::BaseClient;

                Trader( const Trader& ) = delete;
                Trader& operator=( const Trader& ) = delete;

    void        notifyError( const std::string& text );

    void        notifyCancelOrderSuccess( const orderId_t orderId,
                                          const quantity_t quantity );

    void        notifyCreateOrderSuccess( const orderId_t orderId,
                                          const quantity_t quantity );

    void        notifyTrade( const orderId_t orderId, const price_t price,
                             const quantity_t quantity );
};


} /* namespace pyxchange */


#endif /* TRADER */


/* EOF */

