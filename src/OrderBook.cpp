/**
 * @brief This module implements simulator of exchange
 * @file OrderBook.cpp
 *
 */


#include "OrderBook.hpp"
#include "Exception.hpp"
#include "Constants.hpp"
#include "Client.hpp"
#include "Trader.hpp"
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
        logger.warning( boost::format( format::logWrongSide ) % trader->getName() );

        trader->notifyError( format::wrongSide.str() );
    }
    catch( const pyexc::OrderIdError& )
    {
        logger.warning( boost::format( format::logWrongOrderId ) % trader->getName() );

        trader->notifyError( format::wrongOrderId.str() );
    }
    catch( const pyexc::PriceError& )
    {
        logger.warning( boost::format( format::logWrongPrice ) % trader->getName() );

        trader->notifyError( format::wrongPrice.str() );
    }
    catch( const pyexc::QuantityError& )
    {
        logger.warning( boost::format( format::logWrongQuantity ) % trader->getName() );

        trader->notifyError( format::wrongQuantity.str() );
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



/**
 * @brief FIXME
 *
 */
void OrderBook::notifyAllClients( const boost::python::object& data ) const
{
    for( const auto& client : *clients )
    {
        const auto& client_ = client.lock(); // from weak_ptr to shared_ptr

        if( client_ )
        {
            client_->writeData( data );
        }
    }
}


} /* namespace pyxchange */



/* EOF */

