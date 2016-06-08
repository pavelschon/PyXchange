/**
 * @brief This module implements simulator of exchange
 * @file Matcher.cpp
 *
 */


#include "logger/Logger.hpp"


namespace pyxchange
{


namespace py = boost::python;


namespace level
{

const std::string debug     = "debug";
const std::string info      = "info";
const std::string warning   = "warning";
const std::string error     = "error";

} /* namespace log */


/**
 * @brief Constructor
 *
 */
Logger::Logger()
{

}



/**
 * @brief Constructor
 *
 */
Logger::Logger( const boost::python::object& logger_):
    logger{ logger_ }
{

}


/**
 * @brief FIXME
 *
 */
void Logger::debug( const boost::format& message )  const
{
    log( level::debug, message );
}


/**
 * @brief FIXME
 *
 */
void Logger::info( const boost::format& message )  const
{
    log( level::info, message );
}


/**
 * @brief FIXME
 *
 */
void Logger::warning( const boost::format& message )  const
{
    log( level::warning, message );
}


/**
 * @brief FIXME
 *
 */
void Logger::error( const boost::format& message )  const
{
    log( level::error, message );
}


/**
 * @brief FIXME
 *
 */
void Logger::log( const std::string& level, const boost::format& message ) const
{
    if( logger != py::object() ) // if logger is not None
    {
        logger.attr( level.c_str() )( message.str() );
    }
}




} /* namespace pyxchange */


/* EOF */

