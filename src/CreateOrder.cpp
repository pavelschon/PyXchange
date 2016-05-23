/**
 * @brief This module implements simulator of exchange
 * @file CreateOrder.cpp
 *
 */


#include "Matcher.hpp"
#include "MatcherUtils.hpp"


namespace pyxchange
{

namespace py = boost::python;




/**
 * @brief FIXME
 *
 */
template<typename... Params>
OrderCreateResult Trader::createOrder( const TraderPtr& trader, Params... params )
{
    const OrderPtr& order = std::make_shared<Order>( trader, params... );
    const auto& orderPair = std::make_pair( order->getId(), order );
    const auto& insResult = trader->orders.insert( orderPair );

    return std::make_pair( order, insResult.second );
}


/**
 * @brief FIXME
 *
 */
void Matcher::createOrder( const TraderPtr& trader, const boost::python::dict& decoded )
{
    const auto& result = Trader::createOrder( trader, decoded );
    const OrderPtr& order = result.first;

    //const auto OrderCompareGreater = []( const OrderConstPtr& o1, const OrderConstPtr& o2 ) -> bool { return o1->price >= o2->price; };
    //const auto OrderCompareLess    = []( const OrderConstPtr& o1, const OrderConstPtr& o2 ) -> bool { return o1->price <= o2->price; };

    if( !result.second )
    {
        createOrderError( trader, order );
    }
    else if( order->side == side::bid )
    {
        createOrderSuccess( trader, order );

        handleExecutionT<AskOrderContainer, lowerPrice>( askOrders, trader, order, &Order::compareGreater );

        if( order->quantity )
        {
            bidOrders.insert( order );
        }
    }
    else if( order->side == side::ask )
    {
        createOrderSuccess( trader, order );
//         handleAskExecution( trader, order );



        handleExecutionT<BidOrderContainer, higherPrice>( bidOrders, trader, order, &Order::compareLess );

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
void Matcher::createOrderSuccess( const TraderPtr& trader, const OrderPtr& order ) const
{
    py::dict response;

    response[ keys::message ] = message::executionReport;
    response[ keys::report  ] = report::new_;
    response[ keys::orderId ] = order->orderId;

    // send response
    trader->writeData( response );
}



/**
 * @brief FIXME
 *
 */
void Matcher::createOrderError( const TraderPtr& trader, const OrderPtr& order ) const
{
    py::dict response;

    response[ keys::message ] = message::executionReport;
    response[ keys::report  ] = report::err;
    response[ keys::text    ] = strings::orderAlreadyExist;
    response[ keys::orderId ] = order->orderId;

    // send response
    trader->writeData( response );

    PyErr_SetString( PyExc_ValueError, strings::orderAlreadyExist );

    py::throw_error_already_set();
}


} /* namespace pyxchange */



/* EOF */

