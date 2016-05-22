/**
 * @brief This module implements simulator of exchange
 * @file OrderBook.hpp
 *
 */

#ifndef TRADER
#define TRADER

#include "PyXchangeFwd.hpp"
#include "Order.hpp"

#include <boost/python/object.hpp>


namespace pyxchange
{


class Trader
{

public:
    explicit                                Trader( const boost::python::object& write_ );

    void                                    writeString( const char* const data );
    void                                    writeData( const boost::python::object& data );

    size_t                                  cancelOrder( const orderId_t orderId );

    template<typename... Params>
    static std::pair<OrderPtr, bool>        insertOrder( const TraderPtr& trader, Params... params );

    static constexpr const char* const      name = "Trader";

private:
    const boost::python::object             write;

    OrderMap                                orders;
};


/**
 * @brief FIXME
 *
 */
template<typename... Params>
inline std::pair<OrderPtr, bool> Trader::insertOrder( const TraderPtr& trader, Params... params )
{
    const OrderPtr& order = std::make_shared<Order>( trader, params... );
    const auto& orderPair = std::make_pair( order->getId(), order );
    const auto& insResult = trader->orders.insert( orderPair );

    return std::make_pair( order, insResult.second );
}


} /* namespace pyxchange */


#endif /* TRADER */


/* EOF */


