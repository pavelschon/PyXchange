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
    void        notifyCreateOrderSuccess( const orderId_t orderId );
    void        notifyCancelOrderSuccess( const orderId_t orderId );
    void        notifyOrderDoesNotExist( const orderId_t orderId );
    void        notifyOrderAlreadyExist( const orderId_t orderId );
    void        notifySelfMatch( const orderId_t orderId, const orderId_t oppOrderId );
};


} /* namespace pyxchange */


#endif /* TRADER */


/* EOF */

