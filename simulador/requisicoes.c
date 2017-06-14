#include <string.h>
#include "estruturas.h"
#include "requisicoes.h"
#include "manipulations/create.h"
#include "manipulations/write.h"
#include "manipulations/read.h"
#include "manipulations/delete.h"

void print_write_status (int status, char message[] , char file[]);
void print_create_status (int i, char user[]);
void print_delete_status (int status, char file[]);

void requisicoes (Disk *d , FileIndex **fi , int *disk_usage){
  printf ("REQUISICOES\n\n");


  //create files

  
  int posarquivo = create (d , fi , disk_usage , "default" , "teste.txt");
  print_create_status (posarquivo , "teste.txt" );
  printf ("\n");
  
  posarquivo = create (d , fi , disk_usage , "default" , "teste.txt");
  print_create_status (posarquivo , "teste.txt" );
  printf ("\n");
  
  posarquivo = create (d , fi , disk_usage , "default" , "teste1.txt");
  print_create_status (posarquivo , "teste1.txt" );
  printf ("\n");

  char* filePointer = NULL;                       //negativo para demonstrar ponteiro inválido

  char message[] = "lasklasjdfhkljasdfhlaksdjfhaklsdfhklasdfhklasdhfklasdfhlaksdfhaklsdjfhalksdjfhklasdhfkaasdasdasdadasdasdasasdasdasdsadasdasdasdasaskgfakjsgfaskjgfaskjgfaskgaskjdfgaskjdgfaskjgfaskjdgfaskjdgdjgdjfgadjf";
  int status = write (d , fi , disk_usage, "default" ,"teste.txt" , message, strlen(message));
  print_write_status (status, message , "teste.txt" );
  printf ("\n");

  char *mensagem;
  status = read (d , fi , "default" , "teste.txt" , &mensagem);
  printf ("Arquivo: %s\nMensagem: %s\n\n", "teste.txt", mensagem);

  status = write (d , fi , disk_usage, "default" ,"teste1.txt" , message , strlen(message));
  print_write_status (status, message , "teste1.txt" );
  printf ("\n");
   
  status = write (d , fi , disk_usage, "default" ,"teste2.txt" , message , strlen(message));
  print_write_status (status, message , "teste2.txt" );
  printf ("\n");

  status = delete (d , fi , disk_usage , "teste.txt");
  print_delete_status (status, "teste.txt");

}

void  print_delete_status (int status, char file[]){
  switch(status){
    case -2:
      printf ("Erro: arquivo nao encontrado %s\n", file);
      break;
    default:
      printf ("Arquivo %s deletado\n", file);
      break;
  }
}

void  print_write_status (int status, char message[] , char file[]){
  switch(status){
    case -2:
      printf ("Erro: arquivo nao encontrado %s\n", file);
      break;
    default:
      printf ("Arquivo %s escrito\n", file);
      printf ("Message: %s\n" , message);
      break;
  }
}

void print_create_status (int status, char file[]){
  switch (status){
    case -1:
      printf ("Erro: o arquivo %s ja existe\n", file);
      break;
    case -2:
      printf ("Erro: disco cheio\n");
      break;
    default:
      printf ("Arquivo %s criado\n", file);
      break;
  }
} 
