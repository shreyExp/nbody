nbody: nbodyExp.cpp getini.h simout.h getini.o simout.o ProgressBar.hpp
	g++ -o nbody nbodyExp.cpp getini.o simout.o `pkg-config --cflags --libs armadillo jsoncpp opencv`

getini.o: getini.h getini.cpp
	g++ -c getini.cpp `pkg-config --cflags --libs armadillo jsoncpp`

simout.o: simout.h simout.cpp ProgressBar.hpp
	g++ -c simout.cpp `pkg-config --cflags --libs opencv` 
