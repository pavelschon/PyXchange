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

    void                                    operator()( const char* const data );

    static constexpr const char* const      name = "Client";

    const boost::python::object             write;

private:

};


} /* namespace pyxchange */


#endif /* CLIENT */


/* EOF */


