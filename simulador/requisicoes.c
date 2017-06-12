#include <string.h>
#include "estruturas.h"
#include "requisicoes.h"
#include "manipulations/create.h"
#include "manipulations/write.h"
#include "manipulations/open.h"

//#include "manipulations/read.h"

void print_write_status (int status, char file[], char user[]);
void print_create_status (int i, char user[], char status[]);
void print_open_status (int status, char file[], char user[]);

void requisicoes (Disk *d , FileIndex **fi , int *disk_usage){
  printf ("REQUISICOES\n\n");


  //create files

  
  int posarquivo = create (d , fi , disk_usage , "default" , "teste.txt");
  print_create_status (posarquivo , "teste.txt" , "default" );
  printf ("\n");
  
  posarquivo = create (d , fi , disk_usage , "default2" , "teste.txt");
  print_create_status (posarquivo , "teste.txt" , "default2" );
  printf ("\n");
  
  posarquivo = create (d , fi , disk_usage , "default2" , "teste1.txt");
  print_create_status (posarquivo , "teste1.txt" , "default2" );
  printf ("\n");
  



  char* filePointer = NULL;                       //negativo para demonstrar ponteiro inválido

  int status_open = open (d , fi , "default1" , "teste.txt" , filePointer);
  print_open_status (status_open, "teste.txt", "default1");
  printf ("\n");

  status_open = open (d , fi , "default" , "teste.txt" , filePointer);
  print_open_status (status_open, "teste.txt", "default1");
  printf ("\n");

  char message[] = "aasdasdasdadasdasdasasdasdasdsadasdasdasdasaskgfakjsgfaskjgfaskjgfaskgaskjdfgaskjdgfaskjgfaskjdgfaskjdgdjgdjfgadjf";
  int status = write (d , fi , disk_usage, "default" ,"teste.txt" , message, strlen(message));
  print_write_status (status , "teste.txt" , "default");
  printf ("\n");

  status = write (d , fi , disk_usage, "default1" ,"teste.txt" , message , strlen(message));
  print_write_status (status, "teste.txt" , "default1");
  printf ("\n");
   
  status = write (d , fi , disk_usage, "default1" ,"teste2.txt" , message , strlen(message));
  print_write_status (status, "teste2.txt" , "default1");
  printf ("\n");

  status_open = open (d , fi , "default" , "teste.txt" , filePointer);
  print_open_status (status_open, "teste.txt", "default1");
  printf ("\n");

  
  //char block[BLOCK_SIZE];
  //read (d , fi ,  "default" , file , block, BLOCK_SIZE);
  //printf ("%s\n" , block);
  //close (d , fi, "teste.txt");
  //delete (d , fi , "teste.txt");  

}
void  print_open_status (int status, char file[], char user[] , char *filePointer){
  switch(status){
    case -1:
      printf ("Erro: %s tentando abrir %s nao encontrado\n" , user , file);
      break;
    default:
      printf ("Abriu o arquivo %s %li\n", file, filePointer);
      break;
  }
}

void  print_write_status (int status, char file[], char user[]){
  switch(status){
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

void print_create_status (int status, char file[] , char user[]){
  switch (status){
    case -1:
      printf ("Erro: o arquivo %s do usuario %s já existe\n", user, file);
      break;
    case -2:
      printf ("Erro: disco cheio\n");
      break;
    default:
      printf ("Arquivo %s criado pelo usuario %s \n", file, user);
      break;
  }
}
    
