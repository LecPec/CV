CC=g++ -std=c++11 -Xpreprocessor -fopenmp -lomp
CF=-c

all: det_test

det_test: det.o main.o
	$(CC) det.o main.o -o det_test
	rm *.o

det.o: det.cpp 
	$(CC) -c det.cpp

main.o: main.cpp
	$(CC) -c main.cpp

clean:
	rm *.o
