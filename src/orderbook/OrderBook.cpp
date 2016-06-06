/**
 * @brief This module implements simulator of exchange
 * @file OrderBook.cpp
 *
 */


#include "orderbook/OrderBook.hpp"
#include "client/Trader.hpp"
#include "Exception.hpp"
#include "Constants.hpp"
#include "Side.hpp"


namespace pyxchange
{


namespace py = boost::python;


/**
 * @brief Constructor
 *
 */
OrderBook::OrderBook( const ClientSetConstPtr & clients_ ):
    clients{ clients_ }
{

}


/**
 * @brief Constructor
 *
 */
OrderBook::OrderBook( const ClientSetConstPtr & clients_, const Logger& logger_ ):
      logger{ logger_ }
    , clients{ clients_ }
{

}


/**
 * @brief FIXME
 *
 */
void OrderBook::createOrder( const TraderPtr& trader, const py::dict& decoded )
{
    OrderPtr order;

    try
    {
        order = std::make_shared<Order>( trader, decoded );
    }
    catch( const side::WrongSide& )
    {
        logger.warning( boost::format( format::f1::logWrongSide ) % trader->toString() );

        trader->notifyError( format::f0::wrongSide.str() );
    }
    catch( const pyexc::OrderIdError& )
    {
        logger.warning( boost::format( format::f1::logWrongOrderId ) % trader->toString() );

        trader->notifyError( format::f0::wrongOrderId.str() );
    }
    catch( const pyexc::PriceError& )
    {
        logger.warning( boost::format( format::f1::logWrongPrice ) % trader->toString() );

        trader->notifyError( format::f0::wrongPrice.str() );
    }
    catch( const pyexc::QuantityError& )
    {
        logger.warning( boost::format( format::f1::logWrongQuantity ) % trader->toString() );

        trader->notifyError( format::f0::wrongQuantity.str() );
    }

    if( order && order->isBid() )
    {
        insertOrder<BidOrderContainer, AskOrderContainer>( bidOrders, askOrders, trader, order );
    }
    else if( order && order->isAsk() )
    {
        insertOrder<AskOrderContainer, BidOrderContainer>( askOrders, bidOrders, trader, order );
    }
}


} /* namespace pyxchange */



/* EOF */

