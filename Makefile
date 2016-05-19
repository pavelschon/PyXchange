BOOST_LIB=boost_python-py34
PYTHON_CMD=python3.4
PYTHON_LIB=python3.4
PYTHON_INC=/usr/include/python3.4
PYTHON_LIB_PATH=/usr/lib/python3.4/config-3.4m-x86_64-linux-gnu/
CXX=g++
CXXFLAGS=-Wall -pedantic -fPIC
PYXCHANGE_DEPS=build/pyxchange.o build/MatchingEngine.o


all: pyxchange.so

build/MatchingEngine.o: src/MatchingEngine.cpp src/MatchingEngine.hpp src/PyXchangeFwd.hpp
	$(CXX) $(CXXFLAGS) -c src/MatchingEngine.cpp -o build/MatchingEngine.o -I$(PYTHON_INC)


build/pyxchange.o: src/PyXchange.cpp
	$(CXX) $(CXXFLAGS) -c src/PyXchange.cpp -o build/pyxchange.o -I$(PYTHON_INC)

	
pyxchange.so: $(PYXCHANGE_DEPS)
	$(CXX) $(CXXFLAGS) -shared -o pyxchange.so -rdynamic $(PYXCHANGE_DEPS) -l$(BOOST_LIB) -l$(PYTHON_LIB) -L$(PYTHON_LIB_PATH)

	
test: pyxchange.so
	#$(PYTHON_CMD) -c "import pyxchange; print(pyxchange.MatchingEngine)"
	$(PYTHON_CMD) smoketest.py
	
clean:
	rm -vf build/*.o pyxchange.so

