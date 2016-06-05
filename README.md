# PyXchange
Simulator of limit orderbook written in Python and C++, using python-twisted, boost::python and boost::multi_index

## Architecture overview
- The program implements single thread & single process TCP server driven by Twisted framework.
- The nature of event-driven Twisted creates an effect of parallel environment.
