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
template<typename T, typename E, typename ITERABLE>
inline T translate( const std::function<T(void)>& callback, const E& exc, const ITERABLE& types )
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

