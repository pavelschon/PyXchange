/**
 * @brief This module implements simulator of exchange
 * @file NotifyLevels.cpp
 *
 */

#include "OrderBook.hpp"
#include "Client.hpp"
#include "Trader.hpp"
#include "Utils.hpp"


namespace pyxchange
{


/**
 * @brief FIXME
 *
 */
template<typename OrderContainer>
inline void OrderBook::notifyPriceLevels( const typename OrderContainer::type& orders, const typename OrderContainer::price_set& priceLevels, const boost::python::str& side ) const
{
    for( const auto priceLevel : priceLevels )
    {
        notifyPriceLevel<OrderContainer>( orders, priceLevel, side );
    }
}


/**
 * @brief FIXME
 *
 */
template<typename OrderContainer>
inline void OrderBook::notifyPriceLevel( const typename OrderContainer::type& orders, const price_t priceLevel, const boost::python::str& side ) const
{
    typename OrderContainer::type::template index<tags::idxPrice>::type const &idx                = orders.template get<tags::idxPrice>();
    typename OrderContainer::type::template index<tags::idxPrice>::type::const_iterator it        = idx.lower_bound( priceLevel );
    typename OrderContainer::type::template index<tags::idxPrice>::type::const_iterator const end = idx.upper_bound( priceLevel );

    quantity_t quantity = 0;

    while( it != end )
    {
        quantity += (*it)->quantity;

        ++it;
    }

//     boost::python::dict response;

//     response[ keys::message  ] = message::orderBook;
//     response[ keys::side     ] = side;
//     response[ keys::price    ] = priceLevel;
//     response[ keys::quantity ] = quantity;

//     for( const ClientPtr& client : clients )
//     {
//         client->writeData( response );
//     }
}


template void OrderBook::notifyPriceLevels<BidOrderContainer>(
    const BidOrderContainer::type& orders,
    const BidOrderContainer::price_set& priceLevels,
    const boost::python::str& side
) const;

template void OrderBook::notifyPriceLevels<AskOrderContainer>(
    const AskOrderContainer::type& orders,
    const AskOrderContainer::price_set& priceLevels,
    const boost::python::str& side
) const;

template void OrderBook::notifyPriceLevel<BidOrderContainer>(
    const BidOrderContainer::type& orders,
    const price_t priceLevel,
    const boost::python::str& side
) const;

template void OrderBook::notifyPriceLevel<AskOrderContainer>(
    const AskOrderContainer::type& orders,
    const price_t priceLevel,
    const boost::python::str& side
) const;


} /* namespace pyxchange */


/* EOF */


