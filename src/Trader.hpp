/**
 * @brief This module implements simulator of exchange
 * @file OrderBook.hpp
 *
 */

#ifndef TRADER
#define TRADER

#include "PyXchangeFwd.hpp"


namespace pyxchange
{


class Trader
{
private:
    const std::string                       name;
    const boost::python::object             transport;


public:
    explicit                                Trader(
                                                const std::string& name_,
                                                const boost::python::object& transport_
                                            );

                                            Trader( const Trader& ) = delete;
                                            Trader& operator=( const Trader& ) = delete;

    std::string                             getName( void ) const;

    void                                    disconnect( void );

    void                                    writeString( const std::string& data );
    void                                    writeData( const boost::python::object& data );

    void                                    notifyError( const std::string& text );

    void                                    notifyCreateOrderSuccess( const orderId_t orderId );
    void                                    notifyCancelOrderSuccess( const orderId_t orderId );

    void                                    notifyCreateOrderError(
                                                const orderId_t orderId,
                                                const std::string& text
                                            );

    void                                    notifyCancelOrderError(
                                                const orderId_t orderId,
                                                const std::string& text
                                            );
};


} /* namespace pyxchange */


#endif /* TRADER */


/* EOF */

