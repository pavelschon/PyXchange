#!/usr/bin/env python2.7


import pyxchange


matcher  = pyxchange.Matcher()
matcher2 = pyxchange.Matcher()

print( pyxchange.Matcher )
print( matcher )
print( matcher2 )

trader = pyxchange.Trader()
trader2 = pyxchange.Trader()

print(repr(trader))
print(repr(trader2))

matcher.addTrader(trader)
matcher.addTrader(trader)

trader = trader2
print(repr(trader))
print(repr(trader2))


client = pyxchange.Client()
client2 = pyxchange.Client()
client3 = pyxchange.Client(1,2)

print(repr(client))
print(repr(client2))

matcher.addClient(client)
matcher.addClient(client2)


# EOF




