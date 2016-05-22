/**
 * @brief This module implements simulator of exchange
 * @file OrderBook.hpp
 *
 */

#ifndef TRADER
#define TRADER

#include "PyXchangeFwd.hpp"

#include <boost/python/object.hpp>


namespace pyxchange
{


class Trader
{

public:
    explicit                                Trader( const boost::python::object& write_ );

    void                                    operator()( const char* const data );

    template<typename... Params>
    static std::pair<OrderPtr, bool>        insertOrder( const TraderPtr& trader, Params... params );

    static constexpr const char* const      name = "Trader";

private:
    const boost::python::object             write;

    OrderSet                                orders;
};


/**
 * @brief FIXME
 *
 */
template<typename... Params>
inline std::pair<OrderPtr, bool> Trader::insertOrder( const TraderPtr& trader, Params... params )
{
    const OrderPtr& order = std::make_shared<Order>( trader, params... );

    return std::make_pair( order, trader->orders.insert( order ).second );
}


} /* namespace pyxchange */


#endif /* TRADER */


/* EOF */


