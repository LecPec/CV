CC=g++ -std=c++11 -Xpreprocessor -fopenmp -lomp

all: Poisson

Poisson: PoissonSolver.o main.o
	$(CC) PoissonSolver.o main.o -o Poisson
	rm *.o
PoissonSolver.o: PoissonSolver.cpp
	$(CC) -c PoissonSolver.cpp
main.o: main.cpp
	$(CC) -c main.cpp
clean:
	rm *.o