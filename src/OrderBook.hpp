/**
 * @brief This module implements simulator of exchange
 * @file OrderBook.hpp
 *
 */

#ifndef ORDER_BOOK
#define ORDER_BOOK

#include "PyXchangeFwd.hpp"
#include "OrderContainer.hpp"


namespace pyxchange
{


class OrderBook
{
public:
                                            OrderBook();

private:
    BidOrderContainer                       bidOrders;
    AskOrderContainer                       askOrders;

};


} /* namespace pyxchange */


#endif /* ORDER_BOOK */


/* EOF */


