/**
 * @file   OrdersContainer.hxx
 * @brief  Engine for assembling order book from EOBI messages
 *
 *
 */

#ifndef ORDER_CONTAINER
#define ORDER_CONTAINER

#include "orderbook/Order.hpp"

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/tag.hpp>


namespace pyxchange
{


struct idxPrice {};
struct idxPriceTime {};
struct idxTime {};

typedef std::greater<const price_t>                                             higherPrice;    // comparator ( higher price first -> buy orders )
typedef std::less<const price_t>                                                lowerPrice;     // comparator ( lower  price first -> ask orders )
typedef std::less<const time_t>                                                 lowerTimestamp; // comparator ( lower timestamp first )

typedef boost::multi_index::composite_key_compare<higherPrice, lowerTimestamp>  higherPriceLowerTimestamp;
typedef boost::multi_index::composite_key_compare<lowerPrice,  lowerTimestamp>  lowerPriceLowerTimestamp;

typedef BOOST_MULTI_INDEX_CONST_MEM_FUN( Order, price_t, Order::getPrice)       keyPrice;
typedef BOOST_MULTI_INDEX_CONST_MEM_FUN( Order, prio_t, Order::getTime)         keyTime;
typedef boost::multi_index::composite_key<Order, keyPrice, keyTime>             keyPriceTime;

template<typename Compare, typename CompareNonUnique>
struct OrderContainer
{
    typedef boost::multi_index::multi_index_container<
        OrderPtr,
        boost::multi_index::indexed_by<
            boost::multi_index::ordered_unique<
                boost::multi_index::tag<idxPriceTime>,
                keyPriceTime, Compare>,

        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<idxPrice>,
                keyPrice, CompareNonUnique>,

        boost::multi_index::hashed_unique<
            boost::multi_index::tag<idxTime>,
                keyTime> >
    > type;
};


typedef OrderContainer<higherPriceLowerTimestamp, higherPrice>::type            BidOrderContainer;  // container type for buy orders
typedef OrderContainer<lowerPriceLowerTimestamp,  lowerPrice>::type             AskOrderContainer; // container type for sell orders


} /* namespace pyxchange */


#endif /* ORDER_CONTAINER */


/* EOF */

