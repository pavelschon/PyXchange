/**
 * @brief This module implements simulator of exchange
 * @file BaseClient.hpp
 *
 */

#ifndef BASECLIENT
#define BASECLIENT

#include "PyXchangeFwd.hpp"


namespace pyxchange
{


class BaseClient
{
public:
                BaseClient( const std::string& name_,
                            const boost::python::object& transport_ );

                BaseClient( const Trader& ) = delete;
                BaseClient& operator=( const Trader& ) = delete;
    virtual     ~BaseClient();

    std::string getName( void ) const;

    void        disconnect( void );

    void        writeString( const std::string& data );
    void        writeData( const boost::python::object& data );

private:
    const std::string name;
    const boost::python::object transport;
};


} /* namespace pyxchange */


#endif /* BASECLIENT */


/* EOF */

