/**
 * @brief This module implements simulator of exchange
 * @file Client.hpp
 *
 */

#ifndef CLIENT
#define CLIENT

#include "PyXchangeFwd.hpp"


namespace pyxchange
{


class Client
{

public:
    explicit                                Client( const boost::python::object& write_ );

    void                                    writeString( const char* const data );
    void                                    writeData( const boost::python::object& data );

    void                                    notifyError( const char* const text );

    static void                             addClient( const MatcherPtr& matcher, const ClientPtr& client );
    static void                             removeClient( const MatcherPtr& matcher, const ClientPtr& client );

    static constexpr const char* const      name = "Client";

private:
    const boost::python::object             write;

};


} /* namespace pyxchange */


#endif /* CLIENT */


/* EOF */


