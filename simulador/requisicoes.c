#include <string.h>
#include "estruturas.h"
#include "requisicoes.h"
#include "manipulations/create.h"
#include "manipulations/write.h"

void requisicoes (Disk *d , FileIndex **fi , int *disk_usage){
  printf ("REQUISICOES\n");
  int posarquivo = create (d , fi , disk_usage , "default" , "teste.txt");
  printf ("Arquivo criado %d \n", posarquivo);
  posarquivo = create (d , fi , disk_usage , "default2" , "teste.txt");
  printf ("Arquivo criado %d \n", posarquivo);
  char message[] = "aasdasdasdadasdasdasasdasdasdsadasdasdasdasaskgfakjsgfaskjgfaskjgfaskgaskjdfgaskjdgfaskjgfaskjdgfaskjdgdjgdjfgadjf";
  write (d , fi , disk_usage, "default" ,"teste.txt" , message , strlen(message));
  //int filePointer = -1;               //negativo para demonstrar ponteiro inválido
  //open (d , fi , "teste.txt" , &filePointer);
  //char block[1000];
  //read (d , fi , block);
  //close (d , fi, "teste.txt");
  //delete (d , fi , "teste.txt");

}

