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
template<typename EXC, typename CALLBACK, typename ITERABLE, typename... Params>
inline auto translate( const CALLBACK& callback, const ITERABLE& types, Params... params ) -> decltype( callback( params... ) )
{
    try
    {
        return callback( params... );
    }
    catch( const boost::python::error_already_set& )
    {
        PyObject *type, *value, *traceback;
        PyErr_Fetch( &type, &value, &traceback );

        for( PyObject* type_ : types )
        {
            if( PyErr_GivenExceptionMatches( type, type_ ) )
            {
                throw EXC();
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

