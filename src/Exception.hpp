/**
 * @brief This module implements simulator of exchange
 * @file Order.hpp
 *
 */

#ifndef EXCEPTION
#define EXCEPTION

#include "PyXchangeFwd.hpp"


namespace pyxchange
{


namespace pyexc
{


class JsonDecodeError: public std::exception
{

};


class MalformedMessage: public std::exception
{

};


/**
 * @brief Generic Python-to-C++ exception translator
 *
 */
template<typename CALLBACK, typename EXC, typename ITERABLE>
inline auto translate( const CALLBACK& callback, const EXC& exc, const ITERABLE& types ) -> decltype( callback() )
{
    try
    {
        return callback();
    }
    catch( const boost::python::error_already_set& )
    {
        PyObject *type, *value, *traceback;
        PyErr_Fetch( &type, &value, &traceback );

        for( PyObject* type_ : types )
        {
            if( PyErr_GivenExceptionMatches( type, type_ ) )
            {
                throw exc;
            }
        }

        PyErr_Restore(type, value, traceback);

        throw;
    }
}


} /* namespace pyexc */



} /* namespace pyxchange */


#endif /* EXCEPTION */


/* EOF */

