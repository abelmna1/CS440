all: test

test: test.o
	g++ test.o -o test -g -ldl

test.o: test.cpp
	g++ -c test.cpp -g -ldl

clean:
	rm -f *.o test
