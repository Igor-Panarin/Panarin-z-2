CC = gcc

a.out: main.o
	$(CC) $^

main.o: main.c student.h
	$(CC) -c main.c

clean:
	rm -f main.o

