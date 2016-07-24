/**
 * @brief  Declaration of OrderContainer
 * @file   OrderContainer.hpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */

#ifndef ORDER_CONTAINER_HPP
#define ORDER_CONTAINER_HPP

#include "order/Order.hpp"
#include "order/OrderContainerFwd.hpp"

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


namespace extractors
{

typedef BOOST_MULTI_INDEX_CONST_MEM_FUN( Order, price_t, Order::getPrice )      keyPrice;
typedef BOOST_MULTI_INDEX_CONST_MEM_FUN( Order, prio_t,  Order::getTime )       keyTime;
typedef BOOST_MULTI_INDEX_CONST_MEM_FUN( Order, TraderPtr, Order::getTrader )   keyTrader;
typedef BOOST_MULTI_INDEX_CONST_MEM_FUN( Order, TraderOrderId, Order::getUnique ) keyTraderOrderId;

typedef boost::multi_index::composite_key<Order, keyPrice, keyTime>             keyPriceTime;

} /* namespace extractors */


template<typename ComparePriceTime>
struct OrderContainer
{
    typedef ComparePriceTime cmp_price_time;

    typedef typename boost::tuples::element<0,
        typename cmp_price_time::key_comp_tuple>::type cmp_price;

    typedef std::set<price_t, cmp_price> price_set;

    typedef boost::multi_index::multi_index_container<
        OrderPtr, boost::multi_index::indexed_by<

            boost::multi_index::ordered_unique<                                 // iterate orders during match event
                boost::multi_index::tag<tags::idxPriceTime>,
                    extractors::keyPriceTime, cmp_price_time>,

            boost::multi_index::ordered_non_unique<                             // iterate orders by price levels
                boost::multi_index::tag<tags::idxPrice>,
                    extractors::keyPrice, cmp_price>,

            boost::multi_index::ordered_non_unique<                             // find orders of trader
                boost::multi_index::tag<tags::idxTrader>,
                    extractors::keyTrader >,

            boost::multi_index::hashed_unique<                                  // find order by id
                boost::multi_index::tag<tags::idxTraderOrderId>,
                    extractors::keyTraderOrderId > >

    > container_type;

    container_type container;
};

static_assert( std::is_same<BidOrderContainer::cmp_price, comparators::higherPrice>::value, "higherPrice" );
static_assert( std::is_same<AskOrderContainer::cmp_price, comparators::lowerPrice>::value,  "lowerPrice" );

static_assert( std::is_same<BidOrderContainer::cmp_price_time, comparators::higherPriceLowerTime>::value, "higherPriceLowerTime" );
static_assert( std::is_same<AskOrderContainer::cmp_price_time, comparators::lowerPriceLowerTime>::value,  "lowerPriceLowerTime" );


} /* namespace pyxchange */


#endif /* ORDER_CONTAINER */


/* EOF */

