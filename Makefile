.PHONY: clean

CFLAGS = -std=c++11 -Wall -pedantic -g

test: example2
	./example2

example2: mojagrubaryba.o mgrexample.cc
	g++ $(CFLAGS) mgrexample.cc mojagrubaryba.o -o example2

mojagrubaryba.o: mojagrubaryba.h mojagrubaryba.cc
	g++ $(CFLAGS) mojagrubaryba.cc -c -o mojagrubaryba.o
	
clean:
	rm -rf *.o

clean:
	rm -l mojagrubaryba.*
	rm -f mgrexample	
