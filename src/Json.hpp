/**
 * @brief This module implements simulator of exchange
 * @file Utils.hpp
 *
 */

#ifndef JSON
#define JSON

#include "PyXchangeFwd.hpp"


namespace pyxchange
{


namespace json
{


const auto json_module = boost::python::import( "json" );

/**
    * @brief FIXME
    *
    */
template<typename T>
inline boost::python::object loads( T value )
{
    return json_module.attr( "loads" )( value );
}


/**
    * @brief FIXME
    *
    */
template<typename T>
inline T dumps( const boost::python::object& obj )
{
    return boost::python::extract<T>( json_module.attr( "dumps" )( obj ) );
}


} /* namespace json */


} /* namespace pyxchange */


#endif /* JSON */


/* EOF */

