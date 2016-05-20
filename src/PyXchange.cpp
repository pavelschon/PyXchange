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
template<typename T, typename... Params>
std::shared_ptr<T> make_shared_( Params... parameters )
{
    return std::make_shared<T>( parameters... );
}


BOOST_PYTHON_MODULE( pyxchange )
{
    using namespace ::boost::python;
    using namespace ::pyxchange;

    class_<Client, ClientPtr>( Client::name, no_init )
        .def( "__init__", make_constructor( &make_shared_<Client> ) )
        ;

    class_<Trader, TraderPtr>( Trader::name, no_init )
        .def( "__init__", make_constructor( &make_shared_<Trader> ) )
    ;

    class_<Matcher, MatcherPtr>( Matcher::name, no_init )
        .def( "__init__", make_constructor( &make_shared_<Matcher> ) )
        .def( "addTrader", &Matcher::addTrader, args( "trader" ) )
        .def( "addClient", &Matcher::addClient, args( "client" ) )
    ;
}


/* EOF */

