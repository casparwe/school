CC    = g++

FLAGS = -std=c++11 -g -Wall -pedantic

losingChess: losingChess.cpp losingChessTest.cpp chess.cpp chess.h
	$(CC) $(FLAGS) losingChessTest.cpp losingChess.cpp chess.cpp -o tests.out

tests: tests.cpp chess.cpp chess.h
	$(CC) $(FLAGS) tests.cpp chess.cpp -o tests.out

clean:
	rm -f *.o *.out
