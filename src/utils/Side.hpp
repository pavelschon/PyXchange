/**
 * @brief Forward declarations of PyXchange module
 * @file Side.hpp
 *
 */

#ifndef SIDE_HPP
#define SIDE_HPP

#include "PyXchange.hpp"


namespace pyxchange
{


namespace side
{

const std::string buy   = "BUY";
const std::string sell  = "SELL";

const std::wstring wBuy(  buy.begin(),  buy.end() );
const std::wstring wSell( sell.begin(), sell.end() );

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
inline bool isBid( const side_t side_ )
{
    return side_ == bid_;
}


/**
 * @brief FIXME
 *
 */
inline bool isAsk( const side_t side_ )
{
    return side_ == ask_;
}


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


#endif /* SIDE_HPP */


/* EOF */

