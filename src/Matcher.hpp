/**
 * @brief This module implements simulator of exchange
 * @file Matcher.hpp
 * 
 */

#ifndef MATCHER
#define MATCHER

#include "PyXchangeFwd.hpp"
#include "OrderContainer.hpp"


namespace pyxchange
{


class Matcher
{

public:
                                            Matcher();

    void                                    addTrader( const TraderPtr& trader );
    void                                    addClient( const ClientPtr& client );

    void                                    removeTrader( const TraderPtr& client );
    void                                    removeClient( const ClientPtr& client );

    void                                    handleMessageStr( const TraderPtr& trader, const char* const data );
    void                                    handleMessageDict( const TraderPtr& trader, const boost::python::dict& decoded );

    static constexpr const char* const      name = "Matcher";

private:
    void                                    createOrder( const TraderPtr& trader, const boost::python::dict& decoded );
    void                                    cancelOrder( const TraderPtr& trader, const boost::python::dict& decoded );

    void                                    createOrderSuccess( const TraderPtr& trader, const OrderPtr& order );
    void                                    createOrderError( const TraderPtr& trader, const OrderPtr& order );

    void                                    cancelOrderSuccess( const TraderPtr& trader, const boost::python::dict& decoded );
    void                                    cancelOrderError( const TraderPtr& trader, const boost::python::dict& decoded );

    void                                    handleBidExecution( const TraderPtr& bidTrader, const OrderPtr& bidOrder );
    void                                    handleAskExecution( const TraderPtr& bidTrader, const OrderPtr& askOrder );

    TraderSet                               traders;
    ClientSet                               clients;

    BidOrderContainer                       bidOrders;
    AskOrderContainer                       askOrders;
};


} /* namespace pyxchange */


#endif /* MATCHER */


/* EOF */


