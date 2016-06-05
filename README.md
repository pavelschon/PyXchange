# PyXchange
Simulator of limit orderbook written in **Python** and **C++**, using **python-twisted**, **boost::python** and **boost::multi_index** container.

## Architecture overview
The program implements single process & single thread TCP server, but the nature of event-driven **Twisted** framework creates an effect of parallel environment.

Exchange protocol is JSON based, all messages are separated by newline character `\n`.

### TCP server listens on two channels ###

1. **Private channel** for market participants (traders), by default on port 7001. The protocol is request-response based.

2. **Public channel** for publishing market data (trade statistics and price-level aggregated statistics), by default on port 7002. Public channel is read-only, messages are publised by server to all clients.


### Message create order request ###

The new order is at first tried to match with passive orders in orderbook and if no matching order is found, then the order is inserted to the orderbook.

The message expects following fields:

* `message`: string `createOrder`
* `side`: string (`BUY` or `SELL`)
* `orderId`: unsigned integer greater than zero, must be unique for the trader
* `price`: unsigned integer greater that zero
* `quantity`: unsigned integer greater that zero

**Request**

```{ 'orderId': 1, 'price': 100, 'message': 'createOrder', 'side': 'BUY', 'quantity': 10 }```

**Response**

```{ 'report': 'NEW', 'orderId': 1, 'quantity': 100, 'message': 'executionReport' }```

**Fill response** is sent if the order was matched against passive order in the order book.

```{ 'report': 'FILL', 'orderId': 1, 'message': 'executionReport', 'price': 100, 'quantity': 10}```

If the order was matched agains multiple passive orders, then multiple `FILL` messages will be sent.

If the order has some resting quantity after the match event, then the order will be inserted to the orderbook and `NEW` message will be sent.


**Error response** is sent if the order already exists or if the message contains invalid data

```{'text': 'order already exists', 'message': 'error'}```

**Error self-match response** is sent if the order would match agains orders of the same trader. In this case, no order is matched nether inserted, but error is returned. 

```{'text': 'self-match rejected', 'message': 'error'}```


## Message cancel order request ##

The message expects following fields:

* `message`: string `cancelOrder`, order is searched in bid and ask orders
* `orderId`: unsigned integer greater than zero, order of that ID must exist, else error response is returned

**Request**

```{ 'orderId': 1, 'message': 'cancelOrder' }```

**Response**

```{ 'orderId': 1, 'message': 'executionReport', 'report': 'CANCELED', 'quantity': 1 }```

**Error response**

```{ 'text': 'order does not exists', 'message': 'error' }```

## Message orderbook and trade on public channel ##

FIXME

## Implementation details ##

FIXME


