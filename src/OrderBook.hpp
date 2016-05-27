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

private:
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


