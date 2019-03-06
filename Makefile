nbody: nbodyExp.cpp getini.h videogen.h getini.o videogen.o ProgressBar.hpp
	g++ -o nbody nbodyExp.cpp getini.o videogen.o `pkg-config --cflags --libs armadillo jsoncpp opencv`

getini.o: getini.h getini.cpp
	g++ -c getini.cpp `pkg-config --cflags --libs armadillo jsoncpp`

videogen.o: videogen.h videogen.cpp ProgressBar.hpp
	g++ -c videogen.cpp `pkg-config --cflags --libs opencv` 
