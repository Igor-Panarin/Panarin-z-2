CC = gcc

a.out: main.o search.o autotest.o
	$(CC) $^

main.o: main.c search.h
	$(CC) -c main.c
fun.o: search.c search.h
	$(CC) -c search.c
autotest.o: autotest.c autotest.h
	$(CC) -c autotest.c

clean:
	rm -f main.o search.o autotest.o

