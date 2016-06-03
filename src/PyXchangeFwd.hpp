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


namespace keys
{

const std::string message   = "message";
const std::string report    = "report";
const std::string price     = "price";
const std::string orderId   = "orderId";
const std::string quantity  = "quantity";
const std::string side      = "side";
const std::string text      = "text";
const std::string type      = "type";

} /* namespace keys */


namespace strings
{

const std::string orderAlreadyExist     = "order already exists";
const std::string orderInvalid          = "order is invalid";

const std::string unknownMessage        = "unknown message";
const std::string unknownSide           = "unknown side";

} /* namespace strings */


namespace side
{

const std::string buy   = "BUY";
const std::string sell  = "SELL";

const std::string bid   = "bid";
const std::string ask   = "ask";

const side_t bid_       = 1;
const side_t ask_       = 2;

class WrongSide: public std::exception
{

};


/**
 * @brief FIXME
 *
 */
inline side_t opposite( const side_t side_ )
{
    switch( side_ )
    {
        case bid_: return ask_;
        case ask_: return bid_;
        default:   throw WrongSide();
    }
}


/**
 * @brief FIXME
 *
 */
inline std::string toBuySell( const side_t side_ )
{
    switch( side_ )
    {
        case bid_: return buy;
        case ask_: return sell;
        default:   throw WrongSide();
    }
}


/**
 * @brief FIXME
 *
 */
inline std::string toBidAsk( const side_t side_ )
{
    switch( side_ )
    {
        case bid_: return bid;
        case ask_: return ask;
        default:   throw WrongSide();
    }
}


} /* namespace side */


} /* namespace pyxchange */


#endif /* PYXCHANGEFWD */


/* EOF */

