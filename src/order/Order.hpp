/**
 * @brief   Implementation of Order
 * @file    Order.hpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */

#ifndef ORDER_HPP
#define ORDER_HPP

#include "PyXchange.hpp"


namespace pyxchange
{


class Order
{
    friend class OrderBook;

public:
                        Order( const TraderPtr& trader_,
                               const boost::python::dict& decoded,
                               const bool isMarketOrder_ );

    std::string         toString( void ) const;

    price_t             getPrice( void ) const;
    prio_t              getTime( void ) const;
    orderId_t           getId( void ) const;
    TraderPtr           getTrader( void ) const;
    TraderOrderId       getUnique( void ) const;

    static side_t       extractSide( const boost::python::dict& decoded );
    static orderId_t    extractOrderId( const boost::python::dict& decoded );
    static quantity_t   extractQuantity( const boost::python::dict& decoded );
    static price_t      extractPrice( const bool isMarketOrder_, const side_t side_,
                                      const boost::python::dict& decoded );

private:
    bool                comparePrice( const OrderConstPtr& order ) const;

    const bool          isMarketOrder;
    const TraderWPtr    trader;
    const prio_t        time;
    const side_t        side;
    const orderId_t     orderId;
    const price_t       price;
          quantity_t    quantity;
};


} /* namespace pyxchange */


#endif /* ORDER_HPP */


/* EOF */


