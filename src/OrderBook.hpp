/**
 * @brief This module implements simulator of exchange
 * @file OrderBook.hpp
 *
 */

#ifndef ORDER_BOOK
#define ORDER_BOOK

#include "OrderContainer.hpp"
#include "PyXchangeFwd.hpp"



namespace pyxchange
{


class OrderBook
{
public:
                                            OrderBook();

    void                                    createOrder( const TraderPtr& trader, const boost::python::dict& decoded );
    void                                    cancelOrder( const TraderPtr& trader, const boost::python::dict& decoded );

private:
    void                                    createOrderSuccess( const TraderPtr& trader, const OrderPtr& order );
    void                                    createOrderError( const TraderPtr& trader, const OrderPtr& order );

    void                                    cancelOrderSuccess( const TraderPtr& trader, const boost::python::dict& decoded );
    void                                    cancelOrderError( const TraderPtr& trader, const boost::python::dict& decoded );

    void                                    handleBidExecution( const TraderPtr& bidTrader, const OrderPtr& bidOrder );
    void                                    handleAskExecution( const TraderPtr& bidTrader, const OrderPtr& askOrder );

    BidOrderContainer                       bidOrders;
    AskOrderContainer                       askOrders;
};


} /* namespace pyxchange */


#endif /* ORDER_BOOK */


/* EOF */


