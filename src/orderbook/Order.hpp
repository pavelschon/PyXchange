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
                                            Order( const TraderPtr& trader_,
                                                   const boost::python::dict& decoded );

    price_t                                 getPrice( void ) const;
    prio_t                                  getTime( void ) const;

private:
    const TraderWPtr                        trader;
    const boost::python::str                side;
    const prio_t                            time;
    const orderId_t                         orderId;
    const price_t                           price;
    const quantity_t                        quantity;
};


} /* namespace pyxchange */


#endif /* ORDER */


/* EOF */


