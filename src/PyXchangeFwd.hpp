/**
 * @brief Forward declarations of PyXchange module
 * @file PyXchangeFwd.hpp
 * 
 */

#ifndef PYXCHANGEFWD
#define PYXCHANGEFWD

#include <boost/format.hpp>
#include <boost/python.hpp>

#include <algorithm>
#include <functional>
#include <memory>
#include <chrono>
#include <string>
#include <set>


namespace pyxchange
{


typedef std::chrono::time_point<std::chrono::high_resolution_clock>     prio_t;
typedef unsigned int                                                    price_t;
typedef unsigned int                                                    quantity_t;
typedef unsigned int                                                    orderId_t;
typedef unsigned short                                                  side_t;


class OrderBook;

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


class Trader;
typedef std::shared_ptr<Trader>                                         TraderPtr;
typedef std::weak_ptr<Trader>                                           TraderWPtr;
typedef std::set<TraderWPtr, CompareWeakPtr<Trader> >                   TraderSet;
typedef std::tuple<const TraderPtr, const orderId_t>                    TraderOrderId;


namespace keys
{

const std::string message   = "message";
const std::string report    = "report";
const std::string price     = "price";
const std::string orderId   = "orderId";
const std::string quantity  = "quantity";
const std::string side      = "side";
const std::string text      = "text";

} /* namespace keys */


} /* namespace pyxchange */


#endif /* PYXCHANGEFWD */


/* EOF */

