/**
 * @brief This module implements simulator of exchange
 * @file Matcher.cpp
 *
 */


#include "Matcher.hpp"
#include "orderbook/OrderBook.hpp"
#include "client/Client.hpp"
#include "client/Trader.hpp"
#include "Constants.hpp"
#include "Exception.hpp"
#include "Json.hpp"


namespace pyxchange
{

namespace py = boost::python;


/**
 * @brief FIXME
 *
 */
void Matcher::handleCreateOrder( const TraderPtr& trader, const MatcherPtr& matcher,
                                 const boost::python::dict& decoded )
{
    matcher->findClient( trader );

    matcher->orderbook->createOrder( trader, decoded );
}


/**
 * @brief FIXME
 *
 */
void Matcher::handleCancelOrder( const TraderPtr& trader, const MatcherPtr& matcher,
                                 const boost::python::dict& decoded )
{
    matcher->findClient( trader );

    matcher->orderbook->cancelOrder( trader, decoded );
}


/**
 * @brief FIXME
 *
 */
template<typename T>
void Matcher::handleMessageStr( const T& client, const MatcherPtr& matcher, const std::string& data )
{
    matcher->findClient( client );

    matcher->handleMessageStr( client, data );
}


/**
 * @brief FIXME
 *
 */
template<typename T>
void Matcher::handleMessageDict( const T& client, const MatcherPtr& matcher, const boost::python::dict& decoded )
{
    matcher->findClient( client );

    matcher->handleMessageDict( client, decoded );
}


// template void Matcher::handleMessageStr(
//     const ClientPtr& client, const MatcherPtr& matcher, const std::string& data );
//
// template void Matcher::handleMessageDict(
//     const ClientPtr& client, const MatcherPtr& matcher, const boost::python::dict& decoded );

template void Matcher::handleMessageStr(
    const TraderPtr& trader, const MatcherPtr& matcher, const std::string& data );

template void Matcher::handleMessageDict(
    const TraderPtr& trader, const MatcherPtr& matcher, const boost::python::dict& decoded );


/**
 * @brief FIXME
 *
 */
TraderPtr Matcher::getTrader( const std::string& name, const py::object& transport )
{
    const TraderPtr& trader = std::make_shared<Trader>(
        ( boost::format( format::f1::trader ) % name ).str(), transport );

    traders->insert( trader );

    logger.info( boost::format( format::f1::logGetClient ) % trader->toString() );

    return trader;
}


/**
 * @brief FIXME
 *
 */
void Matcher::removeTrader( const TraderPtr& trader )
{
    const auto& it = findClient( trader );

    orderbook->cancelAllOrders( trader );

    traders->erase( it );

    logger.info( boost::format( format::f1::logRemoveClient ) % trader->toString() );
}


/**
 * @brief FIXME
 *
 */
ClientPtr Matcher::getClient( const std::string& name, const py::object& transport )
{
    const ClientPtr& client = std::make_shared<Client>(
        ( boost::format( format::f1::client ) % name ).str(), transport );

    clients->insert( client );

    orderbook->aggregateAllPriceLevels( client );

    logger.info( boost::format( format::f1::logGetClient ) % client->toString() );

    return client;
}


/**
 * @brief FIXME
 *
 */
void Matcher::removeClient( const ClientPtr& client )
{
    const auto& it = findClient( client );

    clients->erase( it );

    logger.info( boost::format( format::f1::logRemoveClient ) % client->toString() );
}


} /* namespace pyxchange */


/* EOF */

