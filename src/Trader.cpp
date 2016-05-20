/**
 * @brief This module implements simulator of exchange
 * @file Trader.cpp
 *
 */


#include "Trader.hpp"


namespace pyxchange
{


/**
 * @brief Constructor
 *
 */
Trader::Trader( const boost::python::object& write_ ):
      write( write_ )
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


