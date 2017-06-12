#include "estruturas.h"
#include "requisicoes.h"
#include "manipulations/create.h"

void requisicoes (Disk *d , FileIndex *fi){
  printf ("REQUISICOES\n");
  create (d , fi , "teste.txt");
  //int filePointer = -1;               //negativo para demonstrar ponteiro inválido
  //open (d , fi , "teste.txt" , &filePointer);
  //char block[1000];
  //read (d , fi , block);
  //close (d , fi, "teste.txt");
  //delete (d , fi , "teste.txt");

}

