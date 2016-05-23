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
inline void Matcher::notifyPriceLevels( const OrderContainer& orders, const Set& priceLevels, const boost::python::str& side )
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
inline void Matcher::notifyPriceLevel( const OrderContainer& orders, const price_t priceLevel, const boost::python::str& side )
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

    std::cout << "orderbook " << priceLevel << " " << quantity << std::endl;

    for( const ClientPtr& client : clients )
    {
        std::cout << "client " << priceLevel << " " << quantity << std::endl;

        client->writeData( response );
    }
}


/**
 * @brief FIXME
 *
 */
template<typename T>
inline void Matcher::notifyError( const T& client, const char* const text  )
{
    boost::python::dict response;

    response[ keys::message ] = message::executionReport;
    response[ keys::report  ] = report::err;
    response[ keys::text    ] = text;

    // send response
    client->writeData( response );
}


} /* namespace pyxchange */


#endif /* MATCHER_UTILS */


/* EOF */


