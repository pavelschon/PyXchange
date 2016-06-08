/**
 * @brief This module implements simulator of exchange
 * @file OrderBook.hpp
 *
 */

#ifndef ORDERBOOK
#define ORDERBOOK

#include "PyXchangeFwd.hpp"
#include "orderbook/OrderContainer.hpp"
#include "logger/Logger.hpp"


namespace pyxchange
{


class OrderBook
{
public:
    explicit    OrderBook( const ClientSetConstPtr & clients_ );
                OrderBook( const ClientSetConstPtr & clients_, const Logger& logger_ );
                OrderBook( const OrderBook& ) = delete;
    OrderBook& operator=( const OrderBook& ) = delete;

    void        createOrder( const TraderPtr& trader, const boost::python::dict& decoded );
    void        cancelOrder( const TraderPtr& trader, const boost::python::dict& decoded );
    void        cancelAllOrders( const TraderPtr& trader );

    void        aggregateAllPriceLevels( const ClientPtr& client ) const;

private:
    template<typename OrderContainer, typename OppOrderContainer>
    void        insertOrder(        typename OrderContainer::type& orders,
                                    typename OppOrderContainer::type& oppOrders, // opposite orders
                                    const TraderPtr& trader, const OrderPtr& order );

    template<typename OrderContainer>
    size_t      cancelOrder(        typename OrderContainer::type& orders,
                                    const TraderPtr& trader, const orderId_t orderId );

    template<typename OrderContainer>
    size_t      cancelAllOrders(    typename OrderContainer::type& orders,
                                    const TraderPtr& trader, const side_t side_ );

    template<typename OrderContainer>
    void        handleExecution(    typename OrderContainer::type& orders,
                                    const TraderPtr& trader, const OrderPtr& order );

    template<typename OrderContainer>
    bool        handleSelfMatch(    const typename OrderContainer::type& orders,
                                    const TraderPtr& trader, const OrderConstPtr& order) const;

    template<typename OrderContainer>
    void        aggregateSetPriceLevels( const typename OrderContainer::type& orders,
                                    const typename OrderContainer::price_set& priceLevels,
                                    const side_t side_ ) const;

    template<typename OrderContainer>
    void        aggregatePriceLevel( const typename OrderContainer::type& orders,
                                     const price_t price, const side_t side_ ) const;

    template<typename OrderContainer>
    void        aggregateAllPriceLevels( const typename OrderContainer::type& orders,
                                         const ClientPtr& client, const side_t side_ ) const;

    void        notifyExecution( const TraderPtr& trader, const OrderPtr& order,
                                 const OrderPtr& oppOrder, const quantity_t matchQty ) const;

private:
    const Logger                    logger;
    const ClientSetConstPtr         clients;

    BidOrderContainer::type         bidOrders;
    AskOrderContainer::type         askOrders;
};


} /* namespace pyxchange */


#endif /* MATCHER */


/* EOF */


