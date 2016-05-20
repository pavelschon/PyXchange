/**
 * @brief This module implements simulator of exchange
 * @file OrderBook.hpp
 *
 */

#ifndef TRADER
#define TRADER

#include "PyXchangeFwd.hpp"

#include <boost/python/object.hpp>


namespace pyxchange
{


class Trader
{

public:
    explicit                                Trader( const boost::python::object& write_ );

    void                                    operator()( const char* const data );

    static constexpr const char* const      name = "Trader";

    const boost::python::object             write;

private:


};


} /* namespace pyxchange */


#endif /* TRADER */


/* EOF */


