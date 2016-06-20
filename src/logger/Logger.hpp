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

    void        debug( const boost::format& message ) const;
    void        info( const boost::format& message )  const;
    void        warning( const boost::format& message )  const;
    void        error( const boost::format& message )  const;

    static const std::string name;

private:
    static boost::python::object getLogger();

    void        log( const std::string& level, const boost::format& message ) const;

    const boost::python::object logger;
};


} /* namespace pyxchange */


#endif /* LOGGER_HPP */


/* EOF */

