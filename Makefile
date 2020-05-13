nbody: main.o  getini.o simout.o 
	g++ -o main main.o getini.o simout.o `pkg-config --cflags --libs armadillo jsoncpp opencv4` 
	#g++ -o nbody nbodyExp.o getini.o simout.o 

#Here the dependencies are the h files because they get bundeled in the main program
main.o: main.cpp getini.h simout.h ProgressBar.hpp
	g++ -c main.cpp `pkg-config --cflags --libs armadillo jsoncpp opencv4`

#Here the dependencies the h file as it is included in the .cpp file
#and get bundled up in the .o file
getini.o: getini.h getini.cpp
	g++ -c getini.cpp `pkg-config --cflags --libs armadillo jsoncpp`

#Here the dependencies the h file as it is included in the .cpp file
#and get bundled up in the .o file
simout.o: simout.h simout.cpp ProgressBar.hpp
	g++ -c simout.cpp `pkg-config --cflags --libs opencv4`
