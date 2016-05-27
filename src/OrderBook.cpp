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
template<typename... Params>
OrderCreateResult Trader::createOrder( const TraderPtr& trader, Params... params )
{
    const auto& order = std::make_shared<Order>( trader, params... );
    const auto& orderPair = std::make_pair( order->getId(), order );
    const auto& insResult = trader->orders.insert( orderPair );

    return std::make_pair( order, insResult.second );
}


/**
 * @brief FIXME
 *
 */
void OrderBook::createOrder( const MatcherPtr& matcher, const TraderPtr& trader, const boost::python::dict& decoded )
{
    const auto& result = Trader::createOrder( trader, decoded );
    const auto& order  = result.first;

    if( !result.second )
    {
        trader->notifyCreateOrderError( order->orderId, strings::orderAlreadyExist );

        PyErr_SetString( PyExc_ValueError, strings::orderAlreadyExist.c_str() );

        py::throw_error_already_set();
    }
    else if( order->isBid() )
    {
        trader->notifyCreateOrderSuccess( order->orderId );

        handleExecution<AskOrderContainer>( askOrders, matcher, trader, order );

        if( order->quantity )
        {
            bidOrders.insert( order );
        }
    }
    else if( order->isAsk() )
    {
        trader->notifyCreateOrderSuccess( order->orderId );

        handleExecution<BidOrderContainer>( bidOrders, matcher, trader, order );

        if( order->quantity )
        {
            askOrders.insert( order );
        }
    }
}


/**
 * @brief FIXME
 *
 */
void OrderBook::cancelOrder( const MatcherPtr& matcher, const TraderPtr& trader, const boost::python::dict& decoded )
{
    const orderId_t orderId = py::extract<const orderId_t>( decoded[ keys::orderId ] );

    if( trader->cancelOrder( orderId ) )
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
void OrderBook::handleExecution( typename OrderContainer::type& orders, const MatcherConstPtr& matcher, const TraderPtr& trader, const OrderPtr& order )
{
    typename OrderContainer::price_set priceLevels{ order->price };
    typename OrderContainer::type::template index<tags::idxPriceTime>::type  const &idx        = orders.template get<tags::idxPriceTime>();
    typename OrderContainer::type::template index<tags::idxPriceTime>::type::const_iterator it = idx.begin();

    quantity_t totalMatchQuantity = 0;

    while( it != idx.end() && order->comparePrice( *it ) && order->quantity > 0 )
    {
        const auto& oppOrder = *it;
        //const TraderPtr& othTrader = othOrder->trader.lock();
        const quantity_t matchQty  = std::min( order->quantity, oppOrder->quantity );

        order->quantity    -= matchQty;
        oppOrder->quantity -= matchQty;
        totalMatchQuantity += matchQty;

        priceLevels.insert( oppOrder->price );

        if( oppOrder->quantity < 1 )
        {
            orders.template erase( it++ );
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
    typename OrderContainer::type::template index<tags::idxPrice>::type  const &idx               = orders.template get<tags::idxPrice>();
    typename OrderContainer::type::template index<tags::idxPrice>::type::const_iterator it        = idx.lower_bound( priceLevel );
    typename OrderContainer::type::template index<tags::idxPrice>::type::const_iterator const end = idx.upper_bound( priceLevel );

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

