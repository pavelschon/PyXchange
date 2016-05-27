/**
 * @brief Forward declarations of PyXchange module
 * @file PyXchangeFwd.hpp
 * 
 */

#include <boost/python.hpp>

#include <algorithm>
#include <functional>
#include <memory>
#include <chrono>
#include <string>
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

typedef std::map<const orderId_t, const OrderConstPtr>                  OrderMap;
typedef std::pair<const OrderPtr, const bool>                           OrderCreateResult;

typedef std::function<bool(const OrderConstPtr&, const OrderConstPtr&)> OrdersCompare;


class Client;
typedef std::shared_ptr<Client>                                         ClientPtr;
typedef std::set<ClientPtr>                                             ClientSet;


class Trader;
typedef std::shared_ptr<Trader>                                         TraderPtr;
typedef std::weak_ptr<Trader>                                           TraderWPtr;
typedef std::set<TraderPtr>                                             TraderSet;


class Matcher;
typedef std::shared_ptr<Matcher>                                        MatcherPtr;
typedef std::shared_ptr<const Matcher>                                  MatcherConstPtr;


} /* namespace pyxchange */



/* EOF */

