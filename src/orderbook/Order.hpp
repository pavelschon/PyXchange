/**
 * @brief This module implements simulator of exchange
 * @file Order.hpp
 *
 */

#ifndef ORDER
#define ORDER

#include "../PyXchangeFwd.hpp"


namespace pyxchange
{


class Order
{
    friend class OrderBook;

public:
                                            Order( const TraderPtr& trader_,
                                                   const boost::python::dict& decoded );

    price_t                                 getPrice( void ) const;
    time_t                                  getTime( void ) const;

private:
    const TraderWPtr                        trader;
    const boost::python::str                side;

    price_t                                 price;
    time_t                                  time;
    quantity_t                              quantity;
    orderId_t                               orderId;
};


} /* namespace pyxchange */


#endif /* ORDER */


/* EOF */


