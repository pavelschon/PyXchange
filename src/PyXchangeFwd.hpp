/**
 * @brief Forward declarations of PyXchange module
 * @file PyXchangeFwd.hpp
 * 
 */

#include <memory>
#include <string>
#include <vector>


namespace pyxchange
{

class Order;


class OrderBook;


class Client;
typedef std::shared_ptr<Client>             ClientPtr;
typedef std::vector<ClientPtr>              ClientVector;



class Trader;
typedef std::shared_ptr<Trader>             TraderPtr;
typedef std::vector<TraderPtr>              TraderVector;


class MatchingEngine;
typedef std::shared_ptr<MatchingEngine>     MatchingEnginePtr;


} /* namespace pyxchange */



/* EOF */

