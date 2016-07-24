/**
 * @brief   Implementation of orderbook
 * @file    OrderBook.hpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */

#ifndef ORDERBOOK_HPP
#define ORDERBOOK_HPP

#include "PyXchange.hpp"
#include "order_container/OrderContainerFwd.hpp"
#include "logger/Logger.hpp"


namespace pyxchange
{


class OrderBook
{
public:
    explicit    OrderBook( const ClientVectorConstPtr& clients_ );
                OrderBook( const OrderBook& ) = delete;
    OrderBook&  operator=( const OrderBook& ) = delete;

    void        createOrder( const TraderPtr& trader, const boost::python::dict& decoded );
    void        marketOrder( const TraderPtr& trader, const boost::python::dict& decoded );
    void        cancelOrder( const TraderPtr& trader, const boost::python::dict& decoded );
    void        cancelAllOrders( const TraderPtr& trader );
    void        aggregateAllPriceLevels( const ClientPtr& client ) const;

private:
    template<typename OrderContainer, typename OppOrderContainer>
    void        insertOrder( OrderContainer& orders, OppOrderContainer& oppOrders, const TraderPtr& trader, const OrderPtr& order );

    template<typename OrderContainer>
    size_t      cancelOrder( OrderContainer& orders, const TraderPtr& trader, const orderId_t  orderId );

    template<typename OrderContainer>
    size_t      cancelAllOrders( OrderContainer& orders, const TraderPtr& trader, const side_t side_ );

    template<typename OrderContainer>
    void        handleExecution( OrderContainer& orders, const OrderPtr& order );

    template<typename OrderContainer>
    void        aggregateSetPriceLevels( const OrderContainer& orders,
                                         const typename OrderContainer::element_type::price_set& priceLevels, const side_t side_ ) const;

    template<typename OrderContainer>
    void        aggregatePriceLevel( const OrderContainer& orders, const price_t price, const side_t side_ ) const;


    template<typename OrderContainer>
    void        aggregateAllPriceLevels( const OrderContainer& orders, const ClientPtr& client, const side_t side_ ) const;

    void        notifyExecution( const OrderConstPtr& order, const OrderConstPtr& oppOrder, const quantity_t matchQty ) const;

private:
    const Logger                    logger;
    const ClientVectorConstPtr      clients;

    BidOrderContainerPtr            bidOrders;
    AskOrderContainerPtr            askOrders;
};


} /* namespace pyxchange */


#endif /* ORDERBOOK_HPP */


/* EOF */

