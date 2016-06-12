/**
 * @brief   FIXME
 * @file    OrderBookAggrAll.cpp
 *
 */


#include "orderbook/OrderBook.hpp"
#include "client/Client.hpp"
#include "utils/Constants.hpp"
#include "utils/Side.hpp"


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
    const auto& outerIdx = orders.template get<tags::idxPrice>();
    const auto& innerIdx = orders.template get<tags::idxPrice>();
    auto outerIt = outerIdx.begin();

    while( outerIt != outerIdx.end() )
    {
        const price_t priceLevel = (*outerIt)->price;
        quantity_t quantity = 0;

        const auto  innerEnd = innerIdx.upper_bound( priceLevel );
              auto  innerIt  = innerIdx.lower_bound( priceLevel );

        while( innerIt != innerEnd )
        {
            quantity += (*innerIt)->quantity;

            ++outerIt;
            ++innerIt;
        }

        client->notifyOrderBook( priceLevel, side_, quantity );
    }
}


} /* namespace pyxchange */


/* EOF */

