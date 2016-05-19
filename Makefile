BOOST_LIB=boost_python-py34
PYTHON_LIB=python3.4
PYTHON_INC=/usr/include/python3.4
PYTHON_LIB_PATH=/usr/lib/python3.4/config-3.4m-x86_64-linux-gnu/
CXX=g++
CXXFLAGS="-Wall -pedantic"


all:	pyxchange.so


build/pyxchange.o: src/pyxchange.cpp
	g++ -Wall -pedantic -fPIC -c src/pyxchange.cpp -o build/pyxchange.o -I$(PYTHON_INC)

	
pyxchange.so: build/pyxchange.o
	g++ -Wall -pedantic -shared -rdynamic build/pyxchange.o -o pyxchange.so -l$(BOOST_LIB) -l$(PYTHON_LIB) -L$(PYTHON_LIB_PATH)

	
test: pyxchange.so
	python3.4 -c "import pyxchange; print(pyxchange.greet())"

clean:
	rm -vf build/*.o pyxchange.so
