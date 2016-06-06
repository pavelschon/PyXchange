/**
 * @brief Forward declarations of PyXchange module
 * @file PyXchangeFwd.hpp
 * 
 */

#ifndef PYXCHANGEFWD_HPP
#define PYXCHANGEFWD_HPP

#include <boost/format.hpp>
#include <boost/python.hpp>

#include <algorithm>
#include <functional>
#include <initializer_list>
#include <memory>
#include <chrono>
#include <string>
#include <set>


namespace pyxchange
{


typedef std::chrono::time_point<std::chrono::high_resolution_clock>     prio_t;
typedef int                                                             price_t;
typedef int                                                             quantity_t;
typedef int                                                             orderId_t;
typedef unsigned short                                                  side_t;


class OrderBook;
typedef std::unique_ptr<OrderBook>                                      OrderBookPtr;

class Order;
typedef std::shared_ptr<Order>                                          OrderPtr;
typedef std::shared_ptr<Order const>                                    OrderConstPtr;


class Matcher;
typedef std::shared_ptr<Matcher>                                        MatcherPtr;
typedef std::shared_ptr<const Matcher>                                  MatcherConstPtr;


template<typename T>
struct CompareWeakPtr
{
    bool operator()( const std::weak_ptr<const T>& lhs,
                     const std::weak_ptr<const T>& rhs ) const
    {
        const auto& lhs_ = lhs.lock();
        const auto& rhs_ = rhs.lock();

        return ( lhs_ && rhs_ ) ? lhs_ < rhs_ : false;
    }
};


class Client;
typedef std::shared_ptr<Client>                                         ClientPtr;
typedef std::weak_ptr<Client>                                           ClientWPtr;

typedef std::set<ClientWPtr, CompareWeakPtr<Client> >                   ClientSet;
typedef std::shared_ptr<ClientSet>                                      ClientSetPtr;
typedef std::shared_ptr<ClientSet const>                                ClientSetConstPtr;


class Trader;
typedef std::shared_ptr<Trader>                                         TraderPtr;
typedef std::weak_ptr<Trader>                                           TraderWPtr;
typedef std::set<TraderWPtr, CompareWeakPtr<Trader> >                   TraderSet;
typedef std::shared_ptr<TraderSet>                                      TraderSetPtr;
typedef std::tuple<const TraderPtr, const orderId_t>                    TraderOrderId;


inline bool hasattr( const boost::python::object& obj, const char* const attr_ )
{
    return PyObject_HasAttrString( obj.ptr(), attr_ );
}


} /* namespace pyxchange */


#endif /* PYXCHANGEFWD_HPP */


/* EOF */

