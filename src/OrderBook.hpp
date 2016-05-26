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
    void                                    handleExecution( typename OrderContainer::type& orders, const MatcherPtr& matcher,
                                                             const TraderPtr& trader, const OrderPtr& order );

    template<typename OrderContainer>
    void                                    notifyPriceLevels( const typename OrderContainer::type & orders, const typename OrderContainer::price_set& priceLevels,
                                                               const boost::python::str& side ) const;

    template<typename OrderContainer>
    void                                    notifyPriceLevel( const typename OrderContainer::type& orders, const price_t priceLevel,
                                                              const boost::python::str& side ) const;

    BidOrderContainer::type                 bidOrders;
    AskOrderContainer::type                 askOrders;
};


} /* namespace pyxchange */


#endif /* MATCHER */


/* EOF */


