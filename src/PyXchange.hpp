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
#include <vector>


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


class Client;
typedef std::shared_ptr<Client>                                         ClientPtr;
typedef std::weak_ptr<Client>                                           ClientWPtr;

typedef std::vector<ClientWPtr>                                         ClientVector;
typedef std::shared_ptr<ClientVector>                                   ClientVectorPtr;
typedef std::shared_ptr<ClientVector const>                             ClientVectorConstPtr;


class Trader;
typedef std::shared_ptr<Trader>                                         TraderPtr;
typedef std::weak_ptr<Trader>                                           TraderWPtr;
typedef std::tuple<const TraderPtr, const orderId_t>                    TraderOrderId;


} /* namespace pyxchange */


#endif /* PYXCHANGEFWD_HPP */


/* EOF */

