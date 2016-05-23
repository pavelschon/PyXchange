/**
 * @brief This module implements simulator of exchange
 * @file Matcher.hpp
 *
 */

#ifndef MATCHER_UTILS
#define MATCHER_UTILS

#include "PyXchangeFwd.hpp"
#include "Matcher.hpp"
#include "Client.hpp"
#include "Trader.hpp"
#include "Utils.hpp"


namespace pyxchange
{


/**
 * @brief FIXME
 *
 */
template<typename OrderContainer, typename Set>
inline void Matcher::notifyPriceLevels( const OrderContainer& orders, const Set& priceLevels, const boost::python::str& side ) const
{
    for( const auto priceLevel : priceLevels )
    {
        notifyPriceLevel( orders, priceLevel, side );
    }
}


/**
 * @brief FIXME
 *
 */
template<typename OrderContainer>
inline void Matcher::notifyPriceLevel( const OrderContainer& orders, const price_t priceLevel, const boost::python::str& side ) const
{
    typename OrderContainer::template index<tags::idxPrice>::type const &idx                = orders.template get<tags::idxPrice>();
    typename OrderContainer::template index<tags::idxPrice>::type::const_iterator it        = idx.lower_bound( priceLevel );
    typename OrderContainer::template index<tags::idxPrice>::type::const_iterator const end = idx.upper_bound( priceLevel );

    quantity_t quantity = 0;

    while( it != end )
    {
        quantity += (*it)->quantity;

        ++it;
    }

    boost::python::dict response;

    response[ keys::message  ] = message::orderBook;
    response[ keys::side     ] = side;
    response[ keys::price    ] = priceLevel;
    response[ keys::quantity ] = quantity;

    for( const ClientPtr& client : clients )
    {
        client->writeData( response );
    }
}


} /* namespace pyxchange */


#endif /* MATCHER_UTILS */


/* EOF */


