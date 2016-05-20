/**
 * @brief This module implements simulator of exchange
 * @file Order.cpp
 *
 */


#include "Order.hpp"


namespace pyxchange
{

namespace py = boost::python;


/**
 * @brief Constructor
 *
 */
Order::Order( const TraderPtr& trader_, const py::str& side_,
              const py::long_& price_, const py::long_& quantity_,
              const py::long_& orderId_ ):

      trader( trader_ )
    , side( side_ )
    , price( py::extract<const price_t>( price_ ) )
    , quantity( py::extract<const quantity_t>( quantity_ ) )
    , orderId( py::extract<const orderId_t>( orderId_ ) )
{

}


} /* namespace pyxchange */



/* EOF */


