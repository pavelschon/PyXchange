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

    void                                    writeString( const std::string& data );
    void                                    writeData( const boost::python::object& data );
    static void                             writeAll( const MatcherConstPtr& matcher, const boost::python::object& data );

    static void                             addClient( const MatcherPtr& matcher, const ClientPtr& client );
    static void                             removeClient( const MatcherPtr& matcher, const ClientPtr& client );

    void                                    notifyError( const std::string& text );

private:
    const boost::python::object             write;

};


} /* namespace pyxchange */


#endif /* CLIENT */


/* EOF */


