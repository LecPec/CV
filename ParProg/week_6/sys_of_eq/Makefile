CC=g++ -std=c++11 -Xpreprocessor -fopenmp -lomp

all: sys

sys: det.o system.o main.o
	$(CC) det.o system.o main.o -o sys
	rm *.o
det.o: ../det/det.cpp
	$(CC) -c ../det/det.cpp
system.o: system.cpp
	$(CC) -c system.cpp
main.o: main.cpp
	$(CC) -c main.cpp

clean:
	rm *.o
