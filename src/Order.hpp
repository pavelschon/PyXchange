/**
 * @brief This module implements simulator of exchange
 * @file Order.hpp
 *
 */

#ifndef ORDER
#define ORDER

#include "PyXchangeFwd.hpp"


namespace pyxchange
{


class Order
{
public:
                                            Order();

    price_t                                 price;
    time_t                                  time;
private:


};


} /* namespace pyxchange */


#endif /* ORDER */


/* EOF */


