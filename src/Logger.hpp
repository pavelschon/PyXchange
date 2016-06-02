/**
 * @brief This module implements simulator of exchange
 * @file BaseClient.hpp
 *
 */

#ifndef LOGGER
#define LOGGER

#include "PyXchangeFwd.hpp"


namespace pyxchange
{


class Logger
{
public:
                                            Logger();
    explicit                                Logger(
                                                const boost::python::object& logger
                                            );

    void                                    debug( const boost::format& message ) const;
    void                                    info( const boost::format& message )  const;
    void                                    warning( const boost::format& message )  const;
    void                                    error( const boost::format& message )  const;

public:
    void                                    log(
                                                const std::string& level,
                                                const boost::format& message
                                            ) const;
private:
    const boost::python::object             logger;
};


} /* namespace pyxchange */


#endif /* BASECLIENT */


/* EOF */

