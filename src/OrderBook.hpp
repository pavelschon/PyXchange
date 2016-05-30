/**
 * @brief This module implements simulator of exchange
 * @file OrderBook.hpp
 *
 */

#ifndef ORDERBOOK
#define ORDERBOOK

#include "PyXchangeFwd.hpp"
#include "OrderContainer.hpp"


namespace pyxchange
{


class OrderBook
{
private:
    BidOrderContainer::type                 bidOrders;
    AskOrderContainer::type                 askOrders;

public:
                                            OrderBook();

    void                                    createOrder(
                                                const MatcherPtr& matcher,
                                                const TraderPtr& trader,
                                                const boost::python::dict& decoded
                                            );

    void                                    cancelOrder(
                                                const MatcherPtr& matcher,
                                                const TraderPtr& trader,
                                                const boost::python::dict& decoded
                                            );

    size_t                                  cancelAllOrders(
                                                const MatcherConstPtr& matcher,
                                                const TraderPtr& trader
                                            );

private:
    template<typename OrderContainer, typename OppOrderContainer>
    void                                    insertOrder(
                                                typename OrderContainer::type& orders,
                                                typename OppOrderContainer::type& oppOrders, // opposite orders
                                                const MatcherConstPtr& matcher,
                                                const TraderPtr& trader,
                                                const OrderPtr& order
                                            );

    template<typename OrderContainer>
    size_t                                  cancelOrder(
                                                typename OrderContainer::type& orders,
                                                const MatcherConstPtr& matcher,
                                                const TraderPtr& trader,
                                                const orderId_t orderId
                                            );

    template<typename OrderContainer>
    size_t                                  cancelAllOrders(
                                                typename OrderContainer::type& orders,
                                                const MatcherConstPtr& matcher,
                                                const TraderPtr& trader,
                                                const side_t side_
                                            );

    template<typename OrderContainer>
    void                                    handleExecution(
                                                typename OrderContainer::type& orders,
                                                const MatcherConstPtr& matcher,
                                                const TraderPtr& trader,
                                                const OrderPtr& order
                                            );

    template<typename OrderContainer>
    void                                    aggregateAllPriceLevels(
                                                const typename OrderContainer::type& orders,
                                                const typename OrderContainer::price_set& priceLevels,
                                                const MatcherConstPtr& matcher,
                                                const side_t side_
                                            ) const;

    template<typename OrderContainer>
    void                                    aggregatePriceLevel(
                                                const typename OrderContainer::type& orders,
                                                const MatcherConstPtr& matcher,
                                                const price_t price,
                                                const side_t side_
                                            ) const;
};


} /* namespace pyxchange */


#endif /* MATCHER */


/* EOF */


