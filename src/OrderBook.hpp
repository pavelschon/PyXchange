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

    void                                    createOrder( const MatcherPtr& matcher, const TraderPtr& trader, const boost::python::dict& decoded );
    void                                    cancelOrder( const MatcherPtr& matcher, const TraderPtr& trader, const boost::python::dict& decoded );

    size_t                                  cancelOrders( const MatcherConstPtr& matcher, const TraderPtr& trader );

private:
    template<typename OrderContainer>
    size_t                                  cancelOrder( typename OrderContainer::type& orders, const MatcherConstPtr& matcher,
                                                         const TraderPtr& trader, const orderId_t orderId );

    template<typename OrderContainer>
    size_t                                  cancelOrders( typename OrderContainer::type& orders, const MatcherConstPtr& matcher,
                                                          const TraderPtr& trader, const side_t side_ );

    template<typename OrderContainer>
    void                                    handleExecution( typename OrderContainer::type& orders, const MatcherConstPtr& matcher,
                                                             const TraderPtr& trader, const OrderPtr& order );

    template<typename OrderContainer>
    void                                    aggregatePriceLevel( const typename OrderContainer::type& orders, const MatcherConstPtr& matcher,
                                                                 const price_t price, const side_t side_ ) const;

    BidOrderContainer::type                 bidOrders;
    AskOrderContainer::type                 askOrders;
};


} /* namespace pyxchange */


#endif /* MATCHER */


/* EOF */


