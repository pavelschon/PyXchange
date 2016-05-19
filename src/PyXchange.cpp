/**
 * @brief This module implements simulator of exchange
 * @file pyxchange.cpp
 * 
 */

#include "MatchingEngine.hpp"

#include <boost/python.hpp>


BOOST_PYTHON_MODULE( pyxchange )
{
    using namespace boost::python;
    using namespace ::pyxchange;
    
    
    class_< MatchingEngine >( "MatchingEngine" )
    ;
    
    def("greet", greet);
}


/* EOF */

