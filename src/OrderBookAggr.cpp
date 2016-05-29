/**
 * @brief This module implements simulator of exchange
 * @file OrderBook.cpp
 *
 */


#include "OrderBook.hpp"
#include "Client.hpp"


namespace pyxchange
{


namespace py = boost::python;


/**
 * @brief FIXME
 *
 */
template<typename OrderContainer>
inline void OrderBook::aggregatePriceLevel( const typename OrderContainer::type& orders, const MatcherConstPtr& matcher,
                                            const price_t priceLevel, const side_t side_ ) const
{
    auto const &idx = orders.template get<tags::idxPrice>();
    auto const end = idx.upper_bound( priceLevel );
    auto it        = idx.lower_bound( priceLevel );

    quantity_t quantity = 0;

    for(; it != end; ++it )
    {
        const auto& order = *it;

        quantity += order->quantity;
    }

    Client::notifyAllOrderBook( matcher, priceLevel, side_, quantity );
}


template void OrderBook::aggregatePriceLevel<BidOrderContainer>(
    const BidOrderContainer::type& orders, const MatcherConstPtr& matcher,
    const price_t priceLevel, const side_t side_ ) const;

template void OrderBook::aggregatePriceLevel<AskOrderContainer>(
    const AskOrderContainer::type& orders, const MatcherConstPtr& matcher,
    const price_t priceLevel, const side_t side_ ) const;


} /* namespace pyxchange */



/* EOF */

