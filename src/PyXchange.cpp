/**
 * @brief This module implements simulator of exchange
 * @file pyxchange.cpp
 * 
 */

#include "PyXchangeFwd.hpp"
#include "Client.hpp"
#include "Trader.hpp"
#include "Matcher.hpp"

#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include <memory>



/**
 * @brief FIXME
 *
 */
template< typename T, typename... Params >
std::shared_ptr<T> constructor( Params... parameters )
{
    std::cout << "creating " << T::name << std::endl;

    return std::make_shared<T>( parameters... );
}


/**
 * @brief Static function sizeof(T)
 *
 */
template< typename T >
size_t sizeof_( void )
{
    return sizeof( T );
}


/**
 * @brief Static function sizeof(T)
 *
 */
template< typename T >
const char* nameof_( void )
{
    return T::name.c_str();
}


BOOST_PYTHON_MODULE( pyxchange )
{
    using namespace ::boost::python;
    using namespace ::pyxchange;

    class_<Client, ClientPtr>( nameof_<Client>(), no_init )
        .def( "__init__", make_constructor( constructor<Client> ) )
        ;

    class_<Trader, TraderPtr>( nameof_<Trader>(), no_init )
        .def( "__init__", make_constructor( constructor<Trader> ) )
    ;

    class_<Matcher, MatcherPtr>( nameof_<Matcher>(), no_init )
        .def( "__init__", make_constructor( constructor<Matcher> ) )
        .def( "addTrader", &Matcher::addTrader )
        .def( "addClient", &Matcher::addClient )
    ;
}


/* EOF */

