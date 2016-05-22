/**
 * @brief This module implements simulator of exchange
 * @file Matcher.hpp
 * 
 */

#ifndef MATCHER
#define MATCHER

#include "PyXchangeFwd.hpp"
#include "OrderBook.hpp"


namespace pyxchange
{


class Matcher
{

public:
                                            Matcher();

    void                                    addTrader( const TraderPtr& trader );
    void                                    addClient( const ClientPtr& client );

    void                                    removeTrader( const TraderPtr& client );
    void                                    removeClient( const ClientPtr& client );

    void                                    handleMessageStr( const TraderPtr& trader,
                                                              const char* const data );

    void                                    handleMessageDict( const TraderPtr& trader,
                                                               const boost::python::dict& decoded );

    static constexpr const char* const      name = "Matcher";

private:
    void                                    createOrder( const TraderPtr& trader,
                                                         const boost::python::dict& decoded );

    OrderBook                               orderbook;

    TraderSet                               traders;
    ClientSet                               clients;
};


} /* namespace pyxchange */


#endif /* MATCHER */


/* EOF */


