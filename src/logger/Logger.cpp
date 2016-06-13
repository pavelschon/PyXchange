/**
 * @brief   Logger wrapper
 * @file    Logger.cpp
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
 * @brief Constructor (no logger)
 *
 */
Logger::Logger()
{

}



/**
 * @brief Constructor (with provided logger)
 * @param logger python object, instance of logging.Logger
 *
 */
Logger::Logger( const boost::python::object& logger_):
    logger{ logger_ }
{

}


/**
 * @brief Log message on debug level
 * @param message to be logged
 *
 */
void Logger::debug( const boost::format& message )  const
{
    log( level::debug, message );
}


/**
 * @brief Log message on info level
 * @param message to be logged
 *
 */
void Logger::info( const boost::format& message )  const
{
    log( level::info, message );
}


/**
 * @brief Log message on warning level
 * @param message to be logged
 *
 */
void Logger::warning( const boost::format& message )  const
{
    log( level::warning, message );
}


/**
 * @brief Log message on error level
 * @param message to be logged
 *
 */
void Logger::error( const boost::format& message )  const
{
    log( level::error, message );
}


/**
 * @brief Log message on any level
 * @param level as string
 * @param message to be logged
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

