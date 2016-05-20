/**
 * @brief This module implements simulator of exchange
 * @file MatchingEngine.cpp
 * 
 */


#include "MatchingEngine.hpp"
#include "Client.hpp"
#include "Trader.hpp"

#include <iostream>


namespace pyxchange
{

const std::string MatchingEngine::name = "MatchingEngine";


/**
 * @brief Constructor
 * 
 */
MatchingEngine::MatchingEngine()
{

}


/**
 * @brief FIXME
 *
 */
void MatchingEngine::addTrader( const MatchingEnginePtr& matcher, const TraderPtr& trader )
{
    matcher->traders.push_back( trader );
}


/**
 * @brief FIXME
 *
 */
void MatchingEngine::addClient( const MatchingEnginePtr& matcher, const ClientPtr& client )
{
    matcher->clients.push_back( client );
}


} /* namespace pyxchange */



/* EOF */

