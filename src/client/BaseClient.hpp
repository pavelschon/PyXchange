/**
 * @brief   Base class implementing shared functionality of Trader and Client
 * @file    BaseClient.hpp
 *
 */

#ifndef BASECLIENT_HPP
#define BASECLIENT_HPP

#include "PyXchange.hpp"
#include "logger/Logger.hpp"


namespace pyxchange
{


class BaseClient
{
    friend class Matcher;

public:
                BaseClient( const MatcherPtr&  matcher_, const std::string& name_,
                            const boost::python::object& handler_ );

                BaseClient( const BaseClient& ) = delete;
    BaseClient& operator=( const BaseClient& ) = delete;
    virtual     ~BaseClient();

    std::string toString( void ) const;

    void        disconnect( void );
    void        logDisconnect( void ) const;

protected:
    void        writeData( const boost::python::object& data );

    const Logger logger;

private:
    const MatcherPtr matcher;
    const std::string name;
    const boost::python::object handler;
};


} /* namespace pyxchange */


#endif /* BASECLIENT_HPP */


/* EOF */

