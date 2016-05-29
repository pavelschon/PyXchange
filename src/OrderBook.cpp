/**
 * @brief This module implements simulator of exchange
 * @file OrderBook.cpp
 *
 */


#include "OrderBook.hpp"
#include "Client.hpp"
#include "Trader.hpp"
#include "Utils.hpp"


namespace pyxchange
{


namespace py = boost::python;


/**
 * @brief Constructor
 *
 */
OrderBook::OrderBook()
{

}


/**
 * @brief FIXME
 *
 */
void OrderBook::createOrder( const MatcherPtr& matcher, const TraderPtr& trader, const boost::python::dict& decoded )
{
    const auto& order  = std::make_shared<Order>( trader, decoded );

    if( order->isBid() && bidOrders.insert( order ).second )
    {
        trader->notifyCreateOrderSuccess( order->orderId );

        handleExecution<AskOrderContainer>( askOrders, matcher, trader, order );
    }
    else if( order->isAsk() && askOrders.insert( order ).second )
    {
        trader->notifyCreateOrderSuccess( order->orderId );

        handleExecution<AskOrderContainer>( askOrders, matcher, trader, order );
    }
    else
    {
        trader->notifyCreateOrderError( order->orderId, strings::orderAlreadyExist );

        PyErr_SetString( PyExc_ValueError, strings::orderAlreadyExist.c_str() );

        py::throw_error_already_set();
    }
}


/**
 * @brief FIXME
 *
 */
void OrderBook::cancelOrder( const MatcherPtr& matcher, const TraderPtr& trader, const boost::python::dict& decoded )
{
    const orderId_t orderId = py::extract<const orderId_t>( decoded[ keys::orderId ] );

    size_t n = 0;

    // we don't know if order is buy or sell, so we cancel it in both containers
    n += cancelOrder<BidOrderContainer>( bidOrders, matcher, trader, orderId );
    n += cancelOrder<AskOrderContainer>( askOrders, matcher, trader, orderId );

    if( n > 0 )
    {
        trader->notifyCancelOrderSuccess( orderId );
    }
    else
    {
        trader->notifyCancelOrderError( orderId, strings::orderDoesNotExist );

        PyErr_SetString( PyExc_ValueError, strings::orderDoesNotExist.c_str() );

        py::throw_error_already_set();
    }
}


/**
 * @brief FIXME
 *
 */
template<typename OrderContainer>
size_t OrderBook::cancelOrder( typename OrderContainer::type& orders, const MatcherConstPtr& matcher,
                               const TraderPtr& trader, const orderId_t orderId )
{
    auto& idx       = orders.template get<tags::idxTraderOrderId>();
    const auto& key = std::make_tuple( trader, orderId );
    const auto  it  = idx.find( key );

    if( it != idx.end() )
    {
        const auto order = *it; // no reference here!

        idx.erase( it );

        aggregatePriceLevel<OrderContainer>( orders, matcher, order->price, order->side );

        return 1;
    }
    else
    {
        return 0;
    }
}


/**
 * @brief FIXME
 *
 */
size_t OrderBook::cancelOrders( const MatcherConstPtr& matcher, const TraderPtr& trader )
{
    size_t n = 0;

    // we don't know if order is buy or sell, so we cancel it in both containers
    n += cancelOrders<BidOrderContainer>( bidOrders, matcher, trader, side::bid_ );
    n += cancelOrders<AskOrderContainer>( askOrders, matcher, trader, side::ask_ );

    return n;
}


/**
 * @brief FIXME
 *
 */
template<typename OrderContainer>
size_t OrderBook::cancelOrders( typename OrderContainer::type& orders, const MatcherConstPtr& matcher,
                                const TraderPtr& trader, const side_t side_ )
{
    typename OrderContainer::price_set priceLevels;

    auto &idx      = orders.template get<tags::idxTrader>();
    auto it        = idx.lower_bound( trader );
    const auto end = idx.upper_bound( trader );

    size_t n = 0;

    while( it != end )
    {
        const auto& order = *it;

        priceLevels.insert( order->price );

        idx.erase( it++ );

        ++n;
    }

    for( const auto price : priceLevels )
    {
        aggregatePriceLevel<OrderContainer>( orders, matcher, price, side_ );
    }

    return n;
}



/**
 * @brief FIXME
 *
 */
template<typename OrderContainer>
void OrderBook::handleExecution( typename OrderContainer::type& orders, const MatcherConstPtr& matcher,
                                 const TraderPtr& trader, const OrderPtr& order )
{
    typename OrderContainer::price_set priceLevels{ order->price };

    auto &idx = orders.template get<tags::idxPriceTime>();
    auto it   = idx.begin();

    quantity_t totalMatchQuantity = 0;

    while( it != idx.end() && order->comparePrice( *it ) && order->quantity > 0 )
    {
        const auto& oppOrder = *it;
        const TraderPtr& oppTrader = oppOrder->getTrader();
        const quantity_t matchQty  = std::min( order->quantity, oppOrder->quantity );

        order->quantity    -= matchQty;
        oppOrder->quantity -= matchQty;
        totalMatchQuantity += matchQty;

        priceLevels.insert( oppOrder->price );

        if( oppOrder->quantity < 1 )
        {
            idx.erase( it++ );
        }
        else
        {
            ++it;
        }
    }

    if( totalMatchQuantity > 0 )
    {
        std::cout << "TRADE=" << totalMatchQuantity << "S=" << orders.template size() << std::endl;

        for( const auto price : priceLevels )
        {
            aggregatePriceLevel<OrderContainer>( orders, matcher, price, side::opposite( order->side ) );
        }
    }
}


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


} /* namespace pyxchange */



/* EOF */

