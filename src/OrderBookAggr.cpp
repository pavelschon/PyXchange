/**
 * @brief This module implements simulator of exchange
 * @file OrderBook.cpp
 *
 */


#include "OrderBook.hpp"
#include "Matcher.hpp"
#include "Trader.hpp"


namespace pyxchange
{


namespace py = boost::python;


namespace message
{

const std::string orderBook          = "orderbook";

} /* namespace message */


template<typename OrderContainer>
void OrderBook::aggregateAllPriceLevels( const typename OrderContainer::type& orders,
                                         const typename OrderContainer::price_set& priceLevels,
                                         const MatcherConstPtr& matcher,const side_t side_ ) const
{
    for( const auto price : priceLevels )
    {
        aggregatePriceLevel<OrderContainer>( orders, matcher, price, side_ );
    }
}


/**
 * @brief FIXME
 *
 */
template<typename OrderContainer>
inline void OrderBook::aggregatePriceLevel( const typename OrderContainer::type& orders,
                                            const MatcherConstPtr& matcher,
                                            const price_t priceLevel, const side_t side_ ) const
{
    const auto& idx = orders.template get<tags::idxPrice>();
    const auto  end = idx.upper_bound( priceLevel );
          auto  it  = idx.lower_bound( priceLevel );

    quantity_t quantity = 0;

    for(; it != end; ++it )
    {
        const auto& order = *it;

        quantity += order->quantity;
    }

    boost::python::dict response;

    response[ keys::message  ] = message::orderBook;
    response[ keys::side     ] = side::toBidAsk( side_ );
    response[ keys::price    ] = priceLevel;
    response[ keys::quantity ] = quantity;

    notifyAllClients( response );
}


template void OrderBook::aggregateAllPriceLevels<BidOrderContainer>(
    const BidOrderContainer::type& orders, const BidOrderContainer::price_set& priceLevels,
    const MatcherConstPtr& matcher, const side_t side_ ) const;

template void OrderBook::aggregateAllPriceLevels<AskOrderContainer>(
    const AskOrderContainer::type& orders, const AskOrderContainer::price_set& priceLevels,
    const MatcherConstPtr& matcher, const side_t side_ ) const;

template void OrderBook::aggregatePriceLevel<BidOrderContainer>(
    const BidOrderContainer::type& orders, const MatcherConstPtr& matcher,
    const price_t priceLevel, const side_t side_ ) const;

template void OrderBook::aggregatePriceLevel<AskOrderContainer>(
    const AskOrderContainer::type& orders, const MatcherConstPtr& matcher,
    const price_t priceLevel, const side_t side_ ) const;


} /* namespace pyxchange */



/* EOF */

