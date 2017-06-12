CC=gcc

all: trabalho

trabalho: main.o simulador.o requisicoes.o create.o simulador/estruturas.h
	$(CC) -std=gnu99 -o DiskManager simulador.o requisicoes.o create.o main.o

main.o: main.c
	$(CC) -std=gnu99 -c main.c

simulador.o: simulador/simulador.c simulador/simulador.h
	$(CC) -std=gnu99 -c simulador/simulador.c

requisicoes.o: simulador/requisicoes.c simulador/requisicoes.h
	$(CC) -std=gnu99 -c simulador/requisicoes.c

create.o: simulador/manipulations/create.c simulador/manipulations/create.h
	$(CC) -std=gnu99 -c simulador/manipulations/create.c

.PHONY: clean

clean:
	rm -rf *.o trabalho
