/**
 * @brief Forward declarations of PyXchange module
 * @file PyXchangeFwd.hpp
 * 
 */

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
typedef std::set<TraderPtr>                 TraderSet;


class Matcher;
typedef std::shared_ptr<Matcher>            MatcherPtr;


typedef unsigned int                        price_t;
typedef unsigned long                       time_t;


} /* namespace pyxchange */



/* EOF */

