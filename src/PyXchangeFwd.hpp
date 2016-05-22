/**
 * @brief Forward declarations of PyXchange module
 * @file PyXchangeFwd.hpp
 * 
 */

#include <boost/python/str.hpp>
#include <boost/python/long.hpp>
#include <boost/python/dict.hpp>
#include <boost/python/extract.hpp>

#include <algorithm>
#include <functional>
#include <memory>
#include <chrono>
#include <string>
#include <utility>
#include <map>
#include <set>


namespace pyxchange
{

typedef std::chrono::time_point<std::chrono::high_resolution_clock>     prio_t;
typedef unsigned int                                                    price_t;
typedef unsigned int                                                    quantity_t;
typedef unsigned int                                                    orderId_t;

class Order;

typedef std::shared_ptr<Order>                                          OrderPtr;
typedef std::shared_ptr<const Order>                                    OrderConstPtr;
typedef std::function<bool(const OrderConstPtr&, const OrderConstPtr&)> OrderComparator;
typedef std::set<OrderPtr, OrderComparator>                             OrderSet;
typedef std::map<orderId_t, OrderPtr>                                   OrderMap;
typedef std::pair<const OrderPtr, const bool>                           OrderCreateResult;

class OrderBook;


class Client;
typedef std::shared_ptr<Client>                                         ClientPtr;
typedef std::set<ClientPtr>                                             ClientSet;


class Trader;
typedef std::shared_ptr<Trader>                                         TraderPtr;
typedef std::weak_ptr<Trader>                                           TraderWPtr;
typedef std::set<TraderPtr>                                             TraderSet;


class Matcher;
typedef std::shared_ptr<Matcher>                                        MatcherPtr;


} /* namespace pyxchange */



/* EOF */

