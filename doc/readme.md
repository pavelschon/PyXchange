# WOOD & Company Coding Challenge 2016 -- starter kit

Přiložené skripty simulují velmi jednoduché klienty burzy. Můžeš je použít k testování své implementace burzovního serveru. V následujících příkladech uvidíš, jak by formát komunikace měl vypadat.

Ke spuštění skriptů budeš potřebovat Python 3.5.

Máš jakékoliv otázky? Piš na [codingchallenge@wood.cz](mailto:codingchallenge@wood.cz).

## client-participant.py

Tento klient simuluje účastníka trhu. V textovém rozhraní ti umožňuje posílat příkazy nebo je rušit, a vypisuje execution reporty přijaté od burzy.

Při spuštění dej skriptu hostname či IP adresu své burzy a port, na kterém burza přijímá privátní spojení od účastníků trhu. Například:

```
./client-participant.py localhost 7001
```

### Příklad: vytvoření a zrušení příkazu (limit orderu)
Všimni si, že burza klientovi potvrdí vytvoření i zrušení příkazu zprávou `executionReport`:

```
./client-participant.py localhost 7001
1: create order, 2: cancel order, q: quit
Command? 1
Side (BUY or SELL)? BUY
Price? 145
Quantity? 350
Assigning order ID 662688

<2016-04-27 12:10:14.490538 sending '{"side": "BUY", "price": 145, "quantity": 350, "message": "createOrder", "orderId": 662688}'>

<2016-04-27 12:10:14.494138 received '{"message": "executionReport", "orderId": 662688, "report": "NEW"}'>

1: create order, 2: cancel order, q: quit
Command? 2
Order ID to cancel? 662688

<2016-04-27 12:10:28.467255 sending '{"message": "cancelOrder", "orderId": 662688}'>

<2016-04-27 12:10:28.474107 received '{"message": "executionReport", "orderId": 662688, "report": "CANCELED"}'>

1: create order, 2: cancel order, q: quit
Command? q
```

### Příklad: vytvoření příkazu (limit orderu), který je následně zobchodován

V tomto příkladu klient vytvoří jeden prodejní příkaz o velikosti 200 akcií. Příkaz je postupně zobchodován po 120, 75, a 5 kusech.

```
./client-participant.py localhost 7001
1: create order, 2: cancel order, q: quit
Command? 1
Side (BUY or SELL)? SELL
Price? 149
Quantity? 200
Assigning order ID 582323

<2016-04-27 13:57:12.339535 sending '{"quantity": 200, "message": "createOrder", "orderId": 582323, "side": "SELL", "price": 149}'>

<2016-04-27 13:57:12.494593 received '{"message": "executionReport", "orderId": 582323, "report": "NEW"}'>

1: create order, 2: cancel order, q: quit
Command?

<2016-04-27 13:57:19.943672 received '{"message": "executionReport", "orderId": 582323, "report": "FILL", "price": 149, "quantity": 120}'>

<2016-04-27 13:57:52.235406 received '{"message": "executionReport", "orderId": 582323, "report": "FILL", "price": 149, "quantity": 75}'>

<2016-04-27 13:57:52.238244 received '{"message": "executionReport", "orderId": 582323, "report": "FILL", "price": 149, "quantity": 5}'>
```


## client-datastream.py
Tento klient pasivně čte veřejná data publikovaná burzou a sestavuje z nich obraz trhu. Po každé přijaté zprávě tedy vypíše, jak aktuálně vypadá order book a jaké na burze proběhly obchody.

Při spuštění dej skriptu hostname či IP adresu své burzy a port, na kterém burza přijímá publikuje veřejná data. Například:

```
./client-participant.py localhost 7002
```

### Příklad 1A: Naplnění order booku

V tomto příkladě začíná burza s prázdným order bookem. Různí účastníci trhu tam posílají své příkazy a ve výstupu klienta tak vidíme, jak se jimi order book plní.

```
./client-datastream.py localhost 7002

<2016-04-27 15:32:30.953503 received '{"type": "orderbook", "side": "bid", "price": 145, "quantity": 100}'>

BID
100 @ 145
ASK
TRADES

<2016-04-27 15:32:30.953664 received '{"type": "orderbook", "side": "ask", "price": 149, "quantity": 500}'>

BID
100 @ 145
ASK
500 @ 149
TRADES

<2016-04-27 15:32:30.953746 received '{"type": "orderbook", "side": "bid", "price": 145, "quantity": 300}'>

BID
300 @ 145
ASK
500 @ 149
TRADES

<2016-04-27 15:32:30.953836 received '{"type": "orderbook", "side": "bid", "price": 144, "quantity": 300}'>

BID
300 @ 145
300 @ 144
ASK
500 @ 149
TRADES

<2016-04-27 15:32:30.953911 received '{"type": "orderbook", "side": "ask", "price": 151, "quantity": 1000}'>

BID
300 @ 145
300 @ 144
ASK
500 @ 149
1000 @ 151
TRADES
```

### Příklad 1B: Na burze probíhá obchod
Order book je stále ve stavu z předchozího příkladu:

```
BID
300 @ 145
300 @ 144
ASK
500 @ 149
1000 @ 151
```

Nyní si představme, že nějaký účastník trhu poslal příkaz "SELL 350 shares at $144". Postupně nám začnou chodit informace o obchodech i změny v orderbooku.

Vidíme, že na ceně 145 byly celkem dva příkazy, které se oba proti příkazu 350 zobchodovaly. Zbývajících 50 akcií se pak zobchodovalo na ceně 144:

```
<2016-04-27 15:32:30.953977 received '{"type": "trade", "time": 1461763950.458236, "price": 145, "quantity": 100}'>

BID
300 @ 145
300 @ 144
ASK
500 @ 149
1000 @ 151
TRADES
2016-04-27 15:32:30.458236 - 100 @ 145

<2016-04-27 15:32:30.954100 received '{"type": "trade", "time": 1461763950.461067, "price": 145, "quantity": 200}'>

BID
300 @ 145
300 @ 144
ASK
500 @ 149
1000 @ 151
TRADES
2016-04-27 15:32:30.458236 - 100 @ 145
2016-04-27 15:32:30.461067 - 200 @ 145

<2016-04-27 15:32:30.954302 received '{"type": "trade", "time": 1461763950.523540, "price": 144, "quantity": 50}'>

BID
300 @ 145
300 @ 144
ASK
500 @ 149
1000 @ 151
TRADES
2016-04-27 15:32:30.458236 - 100 @ 145
2016-04-27 15:32:30.461067 - 200 @ 145
2016-04-27 15:32:30.523540 - 50 @ 144

<2016-04-27 15:32:30.954417 received '{"type": "orderbook", "side": "bid", "price": 145, "quantity": 0}'>

BID
300 @ 144
ASK
500 @ 149
1000 @ 151
TRADES
2016-04-27 15:32:30.458236 - 100 @ 145
2016-04-27 15:32:30.461067 - 200 @ 145
2016-04-27 15:32:30.523540 - 50 @ 144

<2016-04-27 15:32:30.954531 received '{"type": "orderbook", "side": "bid", "price": 144, "quantity": 250}'>

BID
250 @ 144
ASK
500 @ 149
1000 @ 151
TRADES
2016-04-27 15:32:30.458236 - 100 @ 145
2016-04-27 15:32:30.461067 - 200 @ 145
2016-04-27 15:32:30.523540 - 50 @ 144

```
