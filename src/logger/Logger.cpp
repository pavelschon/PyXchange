/**
 * @brief   Logger wrapper
 * @file    Logger.cpp
 *
 */


#include "logger/Logger.hpp"


namespace pyxchange
{


namespace py = boost::python;


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
 * @brief Log message on any level
 * @param level as string
 * @param message to be logged
 *
 */
void Logger::log( const std::string& level, const boost::format& message ) const
{
    logger.attr( level.c_str() )( message.str() );
}


} /* namespace pyxchange */


/* EOF */

