/**
 * @brief This module implements simulator of exchange
 * @file Utils.hpp
 *
 */

#ifndef UTILS
#define UTILS

#include "PyXchangeFwd.hpp"

#include <boost/python/extract.hpp>
#include <boost/python/import.hpp>


namespace pyxchange
{


namespace message
{

const boost::python::str createOrder = "createOrder";
const boost::python::str cancelOrder = "cancelOrder";
const boost::python::str executionReport = "executionReport";


} /* namespace message */


namespace side
{

const boost::python::str bid = "BUY";
const boost::python::str ask = "SELL";


} /* namespace side */


namespace report
{
    const boost::python::str new_ = "NEW";
    const boost::python::str cancel = "CANCELED";
    const boost::python::str err = "ERROR";

} /* namespace report */


const auto json = boost::python::import( "json" );

/**
 * @brief FIXME
 *
 */
template<typename T>
inline boost::python::object json_loads( T value )
{
    return json.attr( "loads" )( value );
}


/**
 * @brief FIXME
 *
 */
template<typename T>
inline T json_dumps( const boost::python::object& obj )
{
    return boost::python::extract<T>( json.attr( "dumps" )( obj ) );
}


} /* namespace pyxchange */


#endif /* UTILS */


/* EOF */

