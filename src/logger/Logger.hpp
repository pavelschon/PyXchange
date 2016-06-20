/**
 * @brief   Logger wrapper
 * @file    Logger.hpp
 *
 */

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "PyXchange.hpp"


namespace pyxchange
{


class Logger
{
public:
                Logger();

    template<typename... Params>
    void        debug( const boost::format& message, Params... params ) const;

    template<typename... Params>
    void        info( const boost::format& message, Params... params )  const;

    template<typename... Params>
    void        warning( const boost::format& message, Params... params )  const;

    template<typename... Params>
    void        error( const boost::format& message, Params... params )  const;

    static const std::string name;

private:
    static boost::python::object getLogger();

    void        log( const std::string& level, const boost::format& message ) const;

    template<typename Param, typename... Params>
    void        log( const std::string& level, const boost::format& message,
                      const Param& param, Params... params ) const;

    const boost::python::object logger;
};


namespace level
{

const std::string debug     = "debug";
const std::string info      = "info";
const std::string warning   = "warning";
const std::string error     = "error";

} /* namespace log */


/**
 * @brief Log message on debug level
 * @param message to be logged
 *
 */
template<typename... Params>
void Logger::debug( const boost::format& message, Params... params )  const
{
    log( level::debug, message, params... );
}


/**
 * @brief Log message on info level
 * @param message to be logged
 *
 */
template<typename... Params>
void Logger::info( const boost::format& message, Params... params )  const
{
    log( level::info, message, params... );
}


/**
 * @brief Log message on warning level
 * @param message to be logged
 *
 */
template<typename... Params>
void Logger::warning( const boost::format& message, Params... params )  const
{
    log( level::warning, message, params... );
}


/**
 * @brief Log message on error level
 * @param message to be logged
 *
 */
template<typename... Params>
void Logger::error( const boost::format& message, Params... params )  const
{
    log( level::error, message, params... );
}


/**
 * @brief Log message on any level
 * @param level as string
 * @param message to be logged
 * @param param formatting parameter
 *
 */
template<typename Param, typename... Params>
inline void Logger::log( const std::string& level, const boost::format& message,
                         const Param& param, Params... params ) const
{
    log( level, boost::format( message ) % param, params... );
}


} /* namespace pyxchange */


#endif /* LOGGER_HPP */


/* EOF */

