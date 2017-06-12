#include <string.h>
#include "estruturas.h"
#include "requisicoes.h"
#include "manipulations/create.h"
#include "manipulations/write.h"
#include "manipulations/open.h"

//#include "manipulations/read.h"

void  print_write_status (int escrita, char file[], char user[]);
void print_create_status (int i, char user[], char message[]);

void requisicoes (Disk *d , FileIndex **fi , int *disk_usage){
  printf ("REQUISICOES\n\n");


  //create files

  
  int posarquivo = create (d , fi , disk_usage , "default" , "teste.txt");
  print_create_status (posarquivo , "default" , "teste.txt");
  printf ("\n");
  
  posarquivo = create (d , fi , disk_usage , "default2" , "teste.txt");
  print_create_status (posarquivo , "default2" , "teste.txt");
  printf ("\n");
  
  posarquivo = create (d , fi , disk_usage , "default2" , "teste1.txt");
  print_create_status (posarquivo , "default2" , "teste1.txt");
  printf ("\n");
  



  int filePointer = -1;                       //negativo para demonstrar ponteiro inválido
  open (d , fi , "teste.txt" , &filePointer);



  char message[] = "aasdasdasdadasdasdasasdasdasdsadasdasdasdasaskgfakjsgfaskjgfaskjgfaskgaskjdfgaskjdgfaskjgfaskjdgfaskjdgdjgdjfgadjf";
  int escrita = write (d , fi , disk_usage, "default" ,"teste.txt" , message , strlen(message));
  print_write_status (escrita , "teste.txt" , "default");
  printf ("\n");

  escrita = write (d , fi , disk_usage, "default1" ,"teste.txt" , message , strlen(message));
  print_write_status (escrita, "teste.txt" , "default1");
  printf ("\n");
   
  escrita = write (d , fi , disk_usage, "default1" ,"teste2.txt" , message , strlen(message));
  print_write_status (escrita, "teste2.txt" , "default1");
  printf ("\n");
  
  //char block[BLOCK_SIZE];
  //read (d , fi ,  "default" , file , block, BLOCK_SIZE);
  //printf ("%s\n" , block);
  //close (d , fi, "teste.txt");
  //delete (d , fi , "teste.txt");

}
void  print_write_status (int escrita, char file[], char user[]){
  switch(escrita){
    case -1:
      printf ("Erro: usuario invalido %s tentando escrever em %s\n" , user , file);
      break;
    case -2:
      printf ("Erro: arquivo nao encontrado %s\n", file);
      break;
    default:
      printf ("Escreveu no arquivo %s\n", file);
      break;
  }
}

void print_create_status (int i, char user[], char message[]){
  switch (i){
    case -1:
      printf ("Erro: o arquivo %s do usuario %s já existe\n", user, message);
      break;
    case -2:
      printf ("Erro: disco cheio\n", message);
      break;
    default:
      printf ("Arquivo criado %s criado pelo usuario %s \n", user, message);
      break;
  }
}
    
