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
public:
                                            OrderBook();
                                            OrderBook( const OrderBook& ) = delete;
                                            OrderBook& operator=( const OrderBook& ) = delete;

    void                                    createOrder(
                                                const MatcherConstPtr& matcher,
                                                const TraderPtr& trader,
                                                const boost::python::dict& decoded
                                            );

    void                                    cancelOrder(
                                                const MatcherConstPtr& matcher,
                                                const TraderPtr& trader,
                                                const boost::python::dict& decoded
                                            );

    void                                    cancelAllOrders(
                                                const MatcherConstPtr& matcher,
                                                const TraderPtr& trader
                                            );

    static ClientPtr                        getClient(
                                                const MatcherPtr& matcher,
                                                const std::string& name,
                                                const boost::python::object& transport
                                            );

    static void                             removeClient(
                                                const MatcherPtr& matcher,
                                                const ClientPtr& client
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
    bool                                    handleSelfMatch(
                                                const typename OrderContainer::type& orders,
                                                const MatcherConstPtr& matcher,
                                                const TraderPtr& trader,
                                                const OrderConstPtr& order
                                            ) const;

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

    void                                    notifyAllClients(
                                                const boost::python::object& data
                                            ) const;

private:
    BidOrderContainer::type                 bidOrders;
    AskOrderContainer::type                 askOrders;

    ClientSet                               clients;
};


} /* namespace pyxchange */


#endif /* MATCHER */


/* EOF */


