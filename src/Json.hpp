/**
 * @brief This module implements simulator of exchange
 * @file Json.hpp
 *
 */

#ifndef JSON_HPP
#define JSON_HPP

#include "PyXchangeFwd.hpp"


namespace pyxchange
{


namespace json
{

namespace attr
{

const char* const json_ = "json";
const char* const loads = "loads";
const char* const dumps = "dumps";

}


const auto json_module = boost::python::import( attr::json_ );


/**
  * @brief FIXME
  *
  */
template<typename T>
inline boost::python::object loads( const T& value )
{
    return json_module.attr( attr::loads )( value );
}


/**
 * @brief FIXME
 *
 */
template<typename T, typename R>
inline R loads( const T& value )
{
    return boost::python::extract<R>( json_module.attr( attr::loads )( value ) );
}


/**
 * @brief FIXME
 *
 */
template<typename T>
inline T dumps( const boost::python::object& obj )
{
    return boost::python::extract<T>( json_module.attr( attr::dumps )( obj ) );
}


} /* namespace json */


} /* namespace pyxchange */


#endif /* JSON_HPP */


/* EOF */

