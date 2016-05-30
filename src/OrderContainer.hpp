/**
 * @file   OrdersContainer.hxx
 * @brief  Engine for assembling order book from EOBI messages
 *
 *
 */

#ifndef ORDER_CONTAINER
#define ORDER_CONTAINER

#include "Order.hpp"

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/tag.hpp>


namespace pyxchange
{


namespace tags
{

struct idxPrice {};
struct idxPriceTime {};
struct idxTraderOrderId {};
struct idxTrader {};

} /* namespace tags */


namespace comparators
{

typedef std::greater<const price_t>                                             higherPrice;    // comparator ( higher price first -> bid orders )
typedef std::less<const price_t>                                                lowerPrice;     // comparator ( lower  price first -> ask orders )
typedef std::less<const prio_t>                                                 lowerTime;      // comparator ( lower timestamp first )

typedef boost::multi_index::composite_key_compare<higherPrice, lowerTime>       higherPriceLowerTime;
typedef boost::multi_index::composite_key_compare<lowerPrice,  lowerTime>       lowerPriceLowerTime;

} /* namespace cmp */


namespace extractors
{

typedef BOOST_MULTI_INDEX_CONST_MEM_FUN( Order, price_t, Order::getPrice )      keyPrice;
typedef BOOST_MULTI_INDEX_CONST_MEM_FUN( Order, prio_t,  Order::getTime )       keyTime;
typedef BOOST_MULTI_INDEX_CONST_MEM_FUN( Order, TraderPtr, Order::getTrader )   keyTrader;
typedef BOOST_MULTI_INDEX_CONST_MEM_FUN( Order, TraderOrderId, Order::getUnique ) keyTraderOrderId;

typedef boost::multi_index::composite_key<Order, keyPrice, keyTime>             keyPriceTime;

} /* namespace extractors */


template<typename ComparePriceTime, typename ComparePrice>
struct OrderContainer
{
    typedef boost::multi_index::multi_index_container<
        OrderPtr, boost::multi_index::indexed_by<

            boost::multi_index::ordered_unique<
                boost::multi_index::tag<tags::idxPriceTime>,
                    extractors::keyPriceTime, ComparePriceTime>,

            boost::multi_index::ordered_non_unique<                             // iterate orders by price levels
                boost::multi_index::tag<tags::idxPrice>,
                    extractors::keyPrice, ComparePrice>,

            boost::multi_index::ordered_non_unique<
                boost::multi_index::tag<tags::idxTrader>,
                    extractors::keyTrader >,

            boost::multi_index::hashed_unique<
                boost::multi_index::tag<tags::idxTraderOrderId>,
                    extractors::keyTraderOrderId > >
    > type;

    typedef std::set<price_t, ComparePrice> price_set;
};


typedef OrderContainer<comparators::higherPriceLowerTime,
                       comparators::higherPrice>                                BidOrderContainer; // container type for buy orders

typedef OrderContainer<comparators::lowerPriceLowerTime,
                       comparators::lowerPrice>                                 AskOrderContainer; // container type for sell orders


} /* namespace pyxchange */


#endif /* ORDER_CONTAINER */


/* EOF */

