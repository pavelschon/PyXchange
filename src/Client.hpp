/**
 * @brief This module implements simulator of exchange
 * @file Client.hpp
 *
 */

#ifndef CLIENT
#define CLIENT

#include "PyXchangeFwd.hpp"

#include <boost/python/object.hpp>



namespace pyxchange
{


class Client
{

public:
    explicit                                Client( const boost::python::object& write_ );

    void                                    writeString( const char* const data );
    void                                    writeData( const boost::python::object& data );

    static constexpr const char* const      name = "Client";

private:
    const boost::python::object             write;

};


} /* namespace pyxchange */


#endif /* CLIENT */


/* EOF */


