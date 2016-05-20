BOOST_LIB=boost_python-py27
PYTHON_CMD=python2.7
PYTHON_LIB=python2.7
PYTHON_INC=/usr/include/python2.7
PYTHON_LIB_PATH=/usr/lib/python2.7/config-x86_64-linux-gnu/
CXX=g++
CXXFLAGS=-Wall -pedantic -fPIC -std=c++14
PYXCHANGE_DEPS=build/Client.o build/Trader.o build/Order.o build/OrderBook.o build/Matcher.o build/pyxchange.o


all: pyxchange.so

test: all
	$(PYTHON_CMD) smoketest.py

clean:
	rm -vf build/*.o pyxchange.so

build/Client.o: src/Client.cpp src/Client.hpp src/PyXchangeFwd.hpp
	$(CXX) $(CXXFLAGS) -o build/Client.o -c src/Client.cpp

build/Trader.o: src/Trader.cpp src/Trader.hpp src/PyXchangeFwd.hpp
	$(CXX) $(CXXFLAGS) -o build/Trader.o -c src/Trader.cpp

build/Order.o: src/Order.cpp src/Order.hpp src/PyXchangeFwd.hpp
	$(CXX) $(CXXFLAGS) -o build/Order.o -c src/Order.cpp

build/OrderBook.o: src/OrderBook.cpp src/OrderBook.hpp src/Order.hpp src/PyXchangeFwd.hpp
	$(CXX) $(CXXFLAGS) -o build/OrderBook.o -c src/OrderBook.cpp

build/Matcher.o: src/Matcher.cpp src/Matcher.hpp src/Client.hpp src/Trader.hpp src/OrderBook.hpp src/PyXchangeFwd.hpp
	$(CXX) $(CXXFLAGS) -o build/Matcher.o -c src/Matcher.cpp


build/pyxchange.o: src/PyXchange.cpp src/PyXchangeFwd.hpp src/Client.hpp src/Trader.hpp src/Matcher.hpp
	$(CXX) $(CXXFLAGS) -o build/pyxchange.o -c src/PyXchange.cpp -I$(PYTHON_INC)

	
pyxchange.so: $(PYXCHANGE_DEPS)
	$(CXX) $(CXXFLAGS) -o pyxchange.so -l$(BOOST_LIB) -l$(PYTHON_LIB) -shared -rdynamic $(PYXCHANGE_DEPS) -L$(PYTHON_LIB_PATH)

	

