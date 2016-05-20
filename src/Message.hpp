/**
 * @brief This module implements simulator of exchange
 * @file Matcher.cpp
 *
 */

#ifndef MESSAGE
#define MESSAGE

#include "PyXchangeFwd.hpp"


namespace pyxchange
{


namespace message
{

const boost::python::str createOrder = "createOrder";


} /* namespace message */


namespace side
{

const boost::python::str bid = "BUY";
const boost::python::str ask = "SELL";


} /* namespace side */


} /* namespace pyxchange */


#endif /* MESSAGE */


/* EOF */

