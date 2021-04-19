CC    = g++

FLAGS = -std=c++11 -g -Wall -pedantic

tests: tests.cpp matris.h
	$(CC) $(FLAGS) tests.cpp -o tests.out

stoiTest: stoiTest.cpp
	$(CC) $(FLAGS) stoiTest.cpp -o stoiTest.out


clean:
	rm -f *.o *.out
