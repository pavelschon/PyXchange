/**
 * @brief This module implements simulator of exchange
 * @file OrderBook.cpp
 *
 */


#include "OrderBook.hpp"
#include "Constants.hpp"
#include "Client.hpp"
#include "Side.hpp"


namespace pyxchange
{

namespace py = boost::python;


/**
 * @brief FIXME
 *
 */
void OrderBook::aggregateAllPriceLevels( const ClientPtr& client ) const
{
    aggregateAllPriceLevels<BidOrderContainer>( bidOrders, client, side::bid_ );
    aggregateAllPriceLevels<AskOrderContainer>( askOrders, client, side::ask_ );
}


/**
 * @brief FIXME
 *
 */
template<typename OrderContainer>
inline void OrderBook::aggregateAllPriceLevels( const typename OrderContainer::type& orders,
                                                const ClientPtr& client, const side_t side_ ) const
{
    const auto& priceTimeIdx = orders.template get<tags::idxPriceTime>();
    const auto& priceIdx     = orders.template get<tags::idxPrice>();
    auto it = priceTimeIdx.begin();

    while( it != priceTimeIdx.end() )
    {

    }
}


} /* namespace pyxchange */


/* EOF */

