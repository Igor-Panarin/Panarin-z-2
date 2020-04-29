CC = gcc

a.out: main.o autotest.o
	$(CC) $^

main.o: main.c autotest.h
	$(CC) -c main.c
autotest.o: autotest.c autotest.h
	$(CC) -c autotest.c

clean:
	rm -f main.o autotest.o

