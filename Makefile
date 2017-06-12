CC=gcc

all: trabalho

makerun: clean trabalho
	./DiskManager

commit:
	git add .
	git commit -m $(m)
	git push origin master

trabalho: simulador.o main.o simulador.o requisicoes.o create.o write.o
	$(CC) -std=gnu99 -o DiskManager create.o write.o requisicoes.o simulador.o main.o 
main.o: main.c
	$(CC) -std=gnu99 -c main.c
simulador.o: simulador/simulador.c simulador/simulador.h
	$(CC) -std=gnu99 -c simulador/simulador.c
requisicoes.o: simulador/requisicoes.c simulador/requisicoes.h
	$(CC) -std=gnu99 -c simulador/requisicoes.c
create.o: simulador/manipulations/create.c simulador/manipulations/create.h
	$(CC) -std=gnu99 -c simulador/manipulations/create.c
write.o: simulador/manipulations/write.c simulador/manipulations/write.h
	$(CC) -std=gnu99 -c simulador/manipulations/write.c

.PHONY: clean

clean:
	rm -rf *.o DiskManager
