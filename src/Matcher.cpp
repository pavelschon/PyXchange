/**
 * @brief This module implements simulator of exchange
 * @file Matcher.cpp
 * 
 */


#include "Matcher.hpp"
#include "Client.hpp"
#include "Trader.hpp"
#include "Json.hpp"


namespace pyxchange
{


namespace py = boost::python;


namespace format
{


const boost::format logMatcherReady( "Matcher is ready" );


} /* namespace message */


namespace message
{

const std::string createOrder        = "createOrder";
const std::string cancelOrder        = "cancelOrder";

} /* namespace message */


/**
 * @brief Constructor
 *
 */
Matcher::Matcher()
{

}



/**
 * @brief Constructor
 * 
 */
Matcher::Matcher( const boost::python::object& logger_):
      logger{ logger_ }
    , orderbook{ logger }
{
    log( log::info, format::logMatcherReady );
}


/**
 * @brief FIXME
 *
 */
void Matcher::log( const std::string& level, const boost::format& message ) const
{
    logger.log( level, message );
}


/**
 * @brief FIXME
 *
 */
void Matcher::handleMessageStr( const TraderPtr& trader, const std::string& data )
{
    const py::dict decoded( json::loads( data ) );

    handleMessageDict( trader, decoded );
}


/**
 * @brief FIXME
 *
 */
void Matcher::handleMessageDict( const TraderPtr& trader, const py::dict& decoded )
{
    const py::str message_type( decoded[ keys::message ] );

    if( message_type == message::createOrder )
    {
        orderbook.createOrder( trader, decoded );
    }
    else if( message_type == message::cancelOrder )
    {
        orderbook.cancelOrder( trader, decoded );
    }
    else
    {
//         log( log::warning, strings::unknownMessage );

        trader->notifyError( strings::unknownMessage );
        trader->disconnect();
    }
}


} /* namespace pyxchange */


/* EOF */

