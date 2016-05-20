/**
 * @brief This module implements simulator of exchange
 * @file pyxchange.cpp
 * 
 */

#include "PyXchangeFwd.hpp"
#include "Client.hpp"
#include "Trader.hpp"
#include "MatchingEngine.hpp"

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

    class_< Client, ClientPtr >( nameof_<Client>(), no_init )
        .def( "__init__", make_constructor( constructor<Client> ) )
        //.def( init<const int64_t, const int64_t, const unsigned int, const unsigned int>() )
        ;

    class_< Trader, TraderPtr >( nameof_<Trader>(), no_init )
        .def( "__init__", make_constructor( constructor<Trader> ) )
        //.def( init<const int64_t, const int64_t, const unsigned int, const unsigned int>() )
    ;

//     class_< TraderVector >( "TraderVector", no_init )
//         .def( vector_indexing_suite< TraderVector >() )
//     ;

    class_< MatchingEngine, MatchingEnginePtr >( MatchingEngine::name.c_str(), no_init )
        .def( "__init__", make_constructor( constructor<MatchingEngine> ) )
        .def( "addTrader", &MatchingEngine::addTrader )
        .def( "addClient", &MatchingEngine::addClient )
    ;
}


/* EOF */

