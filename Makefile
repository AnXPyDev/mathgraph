CC=g++
OBJ=main.o value.o number.o list.o operations.o

main: $(OBJ)
	$(CC) -g -o mathgraph $(OBJ)

main.o:
	$(CC) -c src/main.cpp

value.o:
	$(CC) -c src/algebra/value.cpp

number.o:
	$(CC) -c src/algebra/number.cpp

list.o:
	$(CC) -c src/algebra/list.cpp

operations.o:
	$(CC) -c src/algebra/operations.cpp

clean:
	rm -rf *.o mathgraph
