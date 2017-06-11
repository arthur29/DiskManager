CC=gcc

all: trabalho

trabalho: main.o simulador.o simulador/estruturas.h
	$(CC) -std=gnu99 -o DiskManager simulador/simulador.o main.o

main.o: main.c
	$(CC) -std=gnu99 -c main.c

simulador.o: simulador/simulador.c simulador/simulador.h
	$(CC) -std=gnu99 -c simulador/simulador.c

.PHONY: clean

clean:
	rm -f *.o trabalho
