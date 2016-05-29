/**
 * @brief This module implements simulator of exchange
 * @file Order.hpp
 *
 */

#ifndef ORDER
#define ORDER

#include "PyXchangeFwd.hpp"


namespace pyxchange
{


class Order
{
    friend class OrderBook;

public:
                                            Order( const TraderPtr& trader_, const boost::python::dict& decoded );

    price_t                                 getPrice( void ) const;
    prio_t                                  getTime( void ) const;
    orderId_t                               getId( void ) const;
    TraderPtr                               getTrader( void ) const;

    bool                                    isBid( void ) const;
    bool                                    isAsk( void ) const;

private:
    bool                                    comparePrice( const OrderConstPtr& order ) const;

    static side_t                           extractSide( const TraderPtr& trader_, const boost::python::dict& decoded );

    const TraderWPtr                        trader;
    const side_t                            side;
    const prio_t                            time;
    const orderId_t                         orderId;
    const price_t                           price;
          quantity_t                        quantity;
};


} /* namespace pyxchange */


#endif /* ORDER */


/* EOF */


