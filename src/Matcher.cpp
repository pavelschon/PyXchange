/**
 * @brief This module implements simulator of exchange
 * @file Matcher.cpp
 * 
 */


#include "Matcher.hpp"
#include "Client.hpp"
#include "Trader.hpp"

#include <iostream>


namespace pyxchange
{


/**
 * @brief Constructor
 * 
 */
Matcher::Matcher()
{

}


/**
 * @brief FIXME
 *
 */
void Matcher::addTrader( const MatcherPtr& matcher, const TraderPtr& trader )
{
    matcher->traders.push_back( trader );
}


/**
 * @brief FIXME
 *
 */
void Matcher::addClient( const MatcherPtr& matcher, const ClientPtr& client )
{
    matcher->clients.push_back( client );
}


} /* namespace pyxchange */



/* EOF */

