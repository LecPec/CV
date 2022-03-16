CC=g++ -pthread

all: prod_cuns

prod_cuns: func.o main.o
	$(CC) func.o main.o -o prod_cuns
	rm *.o
func.o: func.cpp
	$(CC) -c func.cpp
main.o: main.cpp
	$(CC) -c main.cpp
clean:
	rm *.o
