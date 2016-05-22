/**
 * @brief This module implements simulator of exchange
 * @file Trader.cpp
 *
 */


#include "Trader.hpp"
#include "Order.hpp"


namespace pyxchange
{


/**
 * @brief Constructor
 *
 */
Trader::Trader( const boost::python::object& write_ ):
      write( write_ )
    , orders( Order::CompareByID() )
{

}


/**
 * @brief FIXME
 *
 */
void Trader::operator()( const char* const data )
{
    write( data );
}


} /* namespace pyxchange */



/* EOF */


