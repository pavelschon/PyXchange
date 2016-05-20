/**
 * @brief Forward declarations of PyXchange module
 * @file PyXchangeFwd.hpp
 * 
 */

#include <boost/python/str.hpp>
#include <boost/python/long.hpp>
#include <boost/python/dict.hpp>
#include <boost/python/extract.hpp>

#include <memory>
#include <string>
#include <vector>
#include <set>


namespace pyxchange
{

class Order;


class OrderBook;


class Client;
typedef std::shared_ptr<Client>             ClientPtr;
typedef std::set<ClientPtr>                 ClientSet;


class Trader;
typedef std::shared_ptr<Trader>             TraderPtr;
typedef std::weak_ptr<Trader>               TraderWPtr;
typedef std::set<TraderPtr>                 TraderSet;


class Matcher;
typedef std::shared_ptr<Matcher>            MatcherPtr;


typedef unsigned int                        price_t;
typedef unsigned long                       time_t;
typedef unsigned int                        quantity_t;
typedef unsigned int                        orderId_t;


} /* namespace pyxchange */



/* EOF */

