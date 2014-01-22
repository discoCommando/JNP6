all:
	g++ mojagrubaryba.h -c -o dupa.o -Wall -std=c++11
	g++ mojagrubaryba.cc -c -o dupa2.o -Wall -std=c++11

clean:
	rm -l mojagrubaryba.*
	
