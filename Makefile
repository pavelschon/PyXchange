BOOST_LIB=boost_python-py34
PYTHON_CMD=python3.4
PYTHON_LIB=python3.4
PYTHON_INC=/usr/include/python3.4
PYTHON_LIB_PATH=/usr/lib/python3.4/config-3.4m-x86_64-linux-gnu/
CXX=g++
CXXFLAGS=-Wall -pedantic -fPIC -std=c++14
PYXCHANGE_DEPS=build/Client.o build/Trader.o build/Order.o build/OrderBook.o build/MatchingEngine.o build/pyxchange.o


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

build/MatchingEngine.o: src/MatchingEngine.cpp src/MatchingEngine.hpp src/Client.hpp src/Trader.hpp src/PyXchangeFwd.hpp
	$(CXX) $(CXXFLAGS) -o build/MatchingEngine.o -c src/MatchingEngine.cpp

build/pyxchange.o: src/PyXchange.cpp src/PyXchangeFwd.hpp src/Client.hpp src/Trader.hpp src/MatchingEngine.hpp
	$(CXX) $(CXXFLAGS) -o build/pyxchange.o -c src/PyXchange.cpp -I$(PYTHON_INC)

	
pyxchange.so: $(PYXCHANGE_DEPS)
	$(CXX) $(CXXFLAGS) -o pyxchange.so -l$(BOOST_LIB) -l$(PYTHON_LIB) -shared -rdynamic $(PYXCHANGE_DEPS) -L$(PYTHON_LIB_PATH)

	

