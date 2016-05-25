/**
 * @brief This module implements simulator of exchange
 * @file Matcher.hpp
 * 
 */

#ifndef MATCHER
#define MATCHER

#include "PyXchangeFwd.hpp"
#include "Client.hpp"
#include "Trader.hpp"
#include "OrderContainer.hpp"


namespace pyxchange
{


class Matcher
{

public:
                                            Matcher();

    friend void                             Client::addClient( const MatcherPtr& matcher, const ClientPtr& client );
    friend void                             Client::removeClient( const MatcherPtr& matcher, const ClientPtr& client );

    friend void                             Trader::addTrader( const MatcherPtr& matcher, const TraderPtr& trader );
    friend void                             Trader::removeTrader( const MatcherPtr& matcher, const TraderPtr& trader );

    static void                             handleMessageStr(  const MatcherPtr& matcher, const TraderPtr& trader, const char* const data );
    static void                             handleMessageDict( const MatcherPtr& matcher, const TraderPtr& trader, const boost::python::dict& decoded );

    static constexpr const char* const      name = "Matcher";

private:
    void                                    handleMessageImpl( const TraderPtr& trader, const boost::python::dict& decoded );

    friend bool                             Trader::checkRegistered( const MatcherPtr& matcher, const TraderPtr& trader );

    void                                    createOrder( const TraderPtr& trader, const boost::python::dict& decoded );
    void                                    cancelOrder( const TraderPtr& trader, const boost::python::dict& decoded );

    void                                    createOrderSuccess( const TraderPtr& trader, const OrderPtr& order ) const;
    void                                    createOrderError(   const TraderPtr& trader, const OrderPtr& order ) const;

    void                                    cancelOrderSuccess( const TraderPtr& trader, const orderId_t orderId ) const;
    void                                    cancelOrderError(   const TraderPtr& trader, const orderId_t orderId ) const;

    template<typename OrderContainer>
    void                                    handleExecution( typename OrderContainer::type& orders, const TraderPtr& trader, const OrderPtr& order );

    template<typename OrderContainer>
    void                                    notifyPriceLevels( const typename OrderContainer::type & orders, const typename OrderContainer::price_set& priceLevels,
                                                               const boost::python::str& side ) const;

    template<typename OrderContainer>
    void                                    notifyPriceLevel( const typename OrderContainer::type& orders, const price_t priceLevel,
                                                              const boost::python::str& side ) const;

    TraderSet                               traders;
    ClientSet                               clients;

    BidOrderContainer::type                 bidOrders;
    AskOrderContainer::type                 askOrders;
};


} /* namespace pyxchange */


#endif /* MATCHER */


/* EOF */


