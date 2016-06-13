/**
 * @brief   JSON encoder and decoder
 * @file    Json.hpp
 *
 */

#ifndef JSON_HPP
#define JSON_HPP

#include "PyXchange.hpp"


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

const size_t maxJsonSize = 200;
const auto json_module = boost::python::import( attr::json_ );


/**
  * @brief Dedode JSON message into python structure
  * @param value JSON string
  *
  */
template<typename T>
inline boost::python::object loads( const T& value )
{
    return json_module.attr( attr::loads )( value );
}


/**
 * @brief Dedode JSON message into any python structure
 * @param value JSON string
 *
 */
template<typename T, typename R>
inline R loads( const T& value )
{
    return boost::python::extract<R>( json_module.attr( attr::loads )( value ) );
}


/**
 * @brief Encode python structure to JSON string
 * @param value python structure
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

