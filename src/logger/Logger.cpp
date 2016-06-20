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


namespace attr
{

const char* const logging   = "logging";
const char* const getLogger = "getLogger";

}

const auto logging_module = boost::python::import( attr::logging );

const std::string Logger::name = "pyxchange";


/**
 * @brief Constructor (no logger)
 *
 */
Logger::Logger(): logger{ getLogger() }
{

}


/**
 * @brief Get pyxchange logger
 * @return logging.Logger instance
 *
 */
py::object Logger::getLogger()
{
    return logging_module.attr( attr::getLogger )( name );
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

