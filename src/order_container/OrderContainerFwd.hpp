/**
 * @brief  Declaration of OrderContainer
 * @file   OrderContainerFwd.hpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */

#ifndef ORDER_CONTAINER_FWD_HPP
#define ORDER_CONTAINER_FWD_HPP

#include "PyXchange.hpp"

#include <boost/multi_index/composite_key.hpp>


namespace pyxchange
{


namespace comparators
{

typedef std::greater<const price_t>                                             higherPrice;    // comparator ( higher price first -> bid orders )
typedef std::less<const price_t>                                                lowerPrice;     // comparator ( lower  price first -> ask orders )
typedef std::less<const prio_t>                                                 lowerTime;      // comparator ( lower timestamp first )

typedef boost::multi_index::composite_key_compare<higherPrice, lowerTime>       higherPriceLowerTime;
typedef boost::multi_index::composite_key_compare<lowerPrice,  lowerTime>       lowerPriceLowerTime;

} /* namespace cmp */


template<typename ComparePriceTime>
struct OrderContainer;

typedef OrderContainer<comparators::higherPriceLowerTime>                       BidOrderContainer; // container type for buy orders
typedef OrderContainer<comparators::lowerPriceLowerTime>                        AskOrderContainer; // container type for sell orders

typedef std::unique_ptr<BidOrderContainer>                                      BidOrderContainerPtr;
typedef std::unique_ptr<AskOrderContainer>                                      AskOrderContainerPtr;


} /* namespace pyxchange */


#endif /* ORDER_CONTAINER_FWD_HPP */


/* EOF */

