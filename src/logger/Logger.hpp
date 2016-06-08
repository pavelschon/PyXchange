/**
 * @brief This module implements simulator of exchange
 * @file Logger.hpp
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
    explicit    Logger( const boost::python::object& logger );

    void        debug( const boost::format& message ) const;
    void        info( const boost::format& message )  const;
    void        warning( const boost::format& message )  const;
    void        error( const boost::format& message )  const;

private:
    void        log( const std::string& level, const boost::format& message ) const;

    const boost::python::object logger;
};


} /* namespace pyxchange */


#endif /* LOGGER_HPP */


/* EOF */

