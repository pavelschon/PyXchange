#!/usr/bin/env python3.4


import pyxchange


matcher  = pyxchange.MatchingEngine()
matcher2 = pyxchange.MatchingEngine()

print( pyxchange.MatchingEngine )
print( matcher )
print( matcher2 )

trader = pyxchange.Trader()
trader2 = pyxchange.Trader()

print(repr(trader))
print(repr(trader2))

matcher.addTrader(trader)
matcher.addTrader(trader2)

trader = trader2
print(repr(trader))
print(repr(trader2))


client = pyxchange.Client()
client2 = pyxchange.Client()

print(repr(client))
print(repr(client2))

matcher.addClient(client)
matcher.addClient(client2)


# EOF




