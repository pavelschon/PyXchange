/**
 * @brief   Exceptions and Python-to-C++ exception translation
 * @file    Exception.hpp
 *
 */

#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include "PyXchange.hpp"


namespace pyxchange
{


namespace pyexc
{


/**
 * @brief   Generic Python-to-C++ exception translator
 *          Caller provides C++ exception class, callback(), list of Python exceptions,
 *          which should be be handled and optional parameterss to callback
 *
 * @param   callback object, usually lambda function, functor, std::bind expression or std::function
 * @param   types list of python exceptions, e.g. { PyExc_ValueError, PyExc_TypeError }
 * @param   params optional parameters to callback()
 * @return  decltype - return value of the callback()
 *
 *          Example:
 *
 *          const auto exceptions = { PyExc_KeyError };
 *          const auto callback = []() { return py::dict()["key"]; }; // throws KeyError when called
 *
 *          try
 *          {
 *              const auto value = translate<std::exception>( callback, exceptions );
 *          }
 *          catch( const std::exception& )
 *          {
 *              std::cout << "key error occured" << std::endl;
 *          }
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


/**
 * @brief       Throw Python exception
 * @param       Python exception
 * @param       format string
 * @return      void
 *
 */
inline void raise( PyObject* type, const boost::format format_ )
{
    PyErr_SetString( type, format_.str().c_str() );

    throw boost::python::error_already_set();
}


class JsonDecodeError: public std::exception
{

};


class JsonTooLong: public std::exception
{

};


class MalformedMessage: public std::exception
{

};


class UnknownMessage: public std::exception
{

};


class PriceError: public std::exception
{

};


class QuantityError: public std::exception
{

};


class OrderIdError: public std::exception
{

};


} /* namespace pyexc */



} /* namespace pyxchange */


#endif /* EXCEPTION_HPP */


/* EOF */

