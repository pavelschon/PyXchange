/**
 * @brief   Implementation of orderbook, message createOrder, marketOrder
 * @file    OrderBook.cpp
 *
 * Copyright (c) 2016 Pavel Schön <pavel@schon.cz>
 *
 */


#include "orderbook/OrderBook.hpp"
#include "client/Trader.hpp"
#include "utils/Exception.hpp"
#include "utils/Constants.hpp"
#include "utils/Side.hpp"


namespace pyxchange
{


namespace py = boost::python;


/**
 * @brief Constructor without logger
 * @param const vector of clients
 *
 */
OrderBook::OrderBook( const ClientVectorConstPtr& clients_ ):
    clients{ clients_ }
{
    logger.info( format::f0::logOrderBookReady );
}


/**
 * @brief Create order from decoded message, notify trader on decoding error
 * @param trader creating order
 * @param decoded message createOrder
 *
 */
void OrderBook::createOrder( const TraderPtr& trader, const py::dict& decoded )
{
    OrderPtr order;

    try
    {
        order = std::make_shared<Order>( trader, decoded, false );
    }
    catch( const side::WrongSide& )
    {
        logger.debug( format::f1::logWrongSide, trader->toString() );

        trader->notifyError( format::f0::wrongSide.str() );
    }
    catch( const pyexc::OrderIdError& )
    {
        logger.debug( format::f1::logWrongOrderId, trader->toString() );

        trader->notifyError( format::f0::wrongOrderId.str() );
    }
    catch( const pyexc::PriceError& )
    {
        logger.debug( format::f1::logWrongPrice, trader->toString() );

        trader->notifyError( format::f0::wrongPrice.str() );
    }
    catch( const pyexc::QuantityError& )
    {
        logger.debug( format::f1::logWrongQuantity, trader->toString() );

        trader->notifyError( format::f0::wrongQuantity.str() );
    }

    if( order && side::isBid( order->side ) )
    {
        insertOrder( bidOrders, askOrders, trader, order );
    }
    else if( order && side::isAsk( order->side ) )
    {
        insertOrder( askOrders, bidOrders, trader, order );
    }
}


/**
 * @brief Create market order from decoded message, notify trader on decoding error
 * @param trader creating order
 * @param decoded message marketOrder
 *
 */
void OrderBook::marketOrder( const TraderPtr& trader, const py::dict& decoded )
{
    OrderPtr order;

    try
    {
        order = std::make_shared<Order>( trader, decoded, true );
    }
    catch( const side::WrongSide& )
    {
        logger.debug( format::f1::logWrongSide, trader->toString() );

        trader->notifyError( format::f0::wrongSide.str() );
    }
    catch( const pyexc::QuantityError& )
    {
        logger.debug( format::f1::logWrongQuantity, trader->toString() );

        trader->notifyError( format::f0::wrongQuantity.str() );
    }

    if( order && side::isBid( order->side ) )
    {
        logger.debug( format::f2::logTraderAddedOrder, trader->toString(), order->toString() );

        handleExecution( askOrders, order );
    }
    else if( order && side::isAsk( order->side ) )
    {
        logger.debug( format::f2::logTraderAddedOrder, trader->toString(), order->toString() );

        handleExecution( bidOrders, order );
    }
}


} /* namespace pyxchange */



/* EOF */

