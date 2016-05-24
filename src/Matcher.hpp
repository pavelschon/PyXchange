/**
 * @brief This module implements simulator of exchange
 * @file Matcher.hpp
 * 
 */

#ifndef MATCHER
#define MATCHER

#include "PyXchangeFwd.hpp"
#include "OrderContainer.hpp"


namespace pyxchange
{


class Matcher
{

public:
                                            Matcher();

    void                                    addTrader( const TraderPtr& trader );
    void                                    addClient( const ClientPtr& client );

    void                                    removeTrader( const TraderPtr& client );
    void                                    removeClient( const ClientPtr& client );

    void                                    handleMessageStr(  const TraderPtr& trader, const char* const data );
    void                                    handleMessageDict( const TraderPtr& trader, const boost::python::dict& decoded );

    static constexpr const char* const      name = "Matcher";

private:
    void                                    handleMessageImpl( const TraderPtr& trader, const boost::python::dict& decoded );

    void                                    createOrder( const TraderPtr& trader, const boost::python::dict& decoded );
    void                                    cancelOrder( const TraderPtr& trader, const boost::python::dict& decoded );

    void                                    createOrderSuccess( const TraderPtr& trader, const OrderPtr& order ) const;
    void                                    createOrderError(   const TraderPtr& trader, const OrderPtr& order ) const;

    void                                    cancelOrderSuccess( const TraderPtr& trader, const orderId_t orderId ) const;
    void                                    cancelOrderError(   const TraderPtr& trader, const orderId_t orderId ) const;

    bool                                    checkTraderExist( const TraderPtr& trader ) const;

    template<typename OrderContainer>
    void                                    handleExecution( OrderContainer& orders, const TraderPtr& trader, const OrderPtr& order );

    template<typename OrderContainer, typename Set>
    void                                    notifyPriceLevels( const OrderContainer& orders, const Set& priceLevels,
                                                               const boost::python::str& side ) const;

    template<typename OrderContainer>
    void                                    notifyPriceLevel( const OrderContainer& orders, const price_t priceLevel,
                                                              const boost::python::str& side ) const;

    TraderSet                               traders;
    ClientSet                               clients;

    BidOrderContainer                       bidOrders;
    AskOrderContainer                       askOrders;
};


} /* namespace pyxchange */


#endif /* MATCHER */


/* EOF */


