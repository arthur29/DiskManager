#include <string.h>
#include "estruturas.h"
#include "requisicoes.h"
#include "manipulations/create.h"
#include "manipulations/write.h"
#include "manipulations/read.h"
#include "manipulations/delete.h"

void print_write_status (int *disk_usage , int status, char message[] , char file[]);
void print_create_status (int *disk_usage , int i, char user[]);
void print_delete_status (int *disk_usage , int status, char file[]);
void print_disk_usage (int *disk_usage);
void print_read_status (int *disk_usage, int status, char mensagem[], char file[]);

void requisicoes (Disk *d , FileIndex **fi , int *disk_usage){
  printf ("REQUISICOES\n\n");


  //create files

  
  int posarquivo = create (d , fi , disk_usage , "default" , "teste.txt");
  print_create_status (disk_usage , posarquivo , "teste.txt" );
  printf ("\n");
  
  posarquivo = create (d , fi , disk_usage , "default" , "teste.txt");
  print_create_status (disk_usage , posarquivo , "teste.txt" );
  printf ("\n");
  
  posarquivo = create (d , fi , disk_usage , "default" , "teste1.txt");
  print_create_status (disk_usage , posarquivo , "teste1.txt" );
  printf ("\n");
  
  posarquivo = create (d , fi , disk_usage , "default" , "teste2.txt");
  print_create_status (disk_usage , posarquivo , "teste2.txt" );
  printf ("\n");

  char* filePointer = NULL;                       //negativo para demonstrar ponteiro inválido

  char message[1000];
  int i;
  message[999] = '\0';
  srand(0);
  for (i=0;i<999;i++){
    message[i] = (rand()%27)+97;
  }
  int status = write (d , fi , disk_usage, "default" ,"teste.txt" , message, strlen(message));
  print_write_status (disk_usage , status, message , "teste.txt" );
  printf ("\n");

  for (i=0;i<999;i++){
    message[i] = (rand()%27)+97;
  }
  status = write (d , fi , disk_usage, "default" ,"teste1.txt" , message , strlen(message));
  print_write_status (disk_usage , status, message , "teste1.txt" );
  printf ("\n");
  
  for (i=0;i<999;i++){
    message[i] = (rand()%27)+97;
  }
  status = write (d , fi , disk_usage, "default" ,"teste2.txt" , message , strlen(message));
  print_write_status (disk_usage , status, message , "teste2.txt" );
  printf ("\n");

  char *mensagem;
  status = read (d , fi , "default" , "teste.txt" , &mensagem);
  print_read_status (disk_usage, status, mensagem, "teste.txt");
  printf ("Arquivo: %s\nMensagem: %s\n\n", "teste.txt", mensagem);
   
  status = read (d , fi , "default" , "teste1.txt" , &mensagem);
  print_read_status (disk_usage, status, mensagem, "teste1.txt");
  printf ("Arquivo: %s\nMensagem: %s\n\n", "teste1.txt", mensagem);

  for (i=0;i<999;i++){
    message[i] = (rand()%27)+97;
  }
  status = write (d , fi , disk_usage, "default" ,"teste2.txt" , message , strlen(message));
  print_write_status (disk_usage , status, message , "teste2.txt" );
  printf ("\n");

  status = delete (d , fi , disk_usage , "teste.txt");
  print_delete_status (disk_usage , status, "teste.txt");

}

void  print_delete_status (int *disk_usage , int status, char file[]){
  switch(status){
    case -2:
      printf ("Erro: arquivo nao encontrado %s\n", file);
      break;
    default:
      printf ("Arquivo %s deletado\n", file);
      break;
  }
  print_disk_usage (disk_usage);
}

void  print_write_status (int *disk_usage , int status, char message[] , char file[]){
  switch(status){
    case -2:
      printf ("Erro: arquivo nao encontrado %s\n", file);
      break;
    case -3:
      printf ("Erro: disco cheio, %s não escrito\n", file);
      break;
    default:
      printf ("Arquivo %s escrito\n", file);
      printf ("Message: %s\n" , message);
      break;
  }
  print_disk_usage (disk_usage);
}
void print_create_status (int *disk_usage , int status, char file[]){
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
  print_disk_usage (disk_usage);
} 

void print_read_status (int *disk_usage, int status, char mensagem[], char file[]){
  switch(status){
    case -1:
      printf ("Erro: arquivo nao encontrado %s\n", file);
      break;
    default:
      printf ("Mensagem: %s\n", mensagem);
      break;
  }
  print_disk_usage (disk_usage);
}
void print_disk_usage (int *disk_usage){
  
  int disk_size = DISK_SIZE;
  int i;

  for (i=0;i<disk_size;i++){
    if (i%5 == 0){
      printf ("---------------------\n");
    }
    printf ("| %d ", disk_usage[i]);
    if (((i+1)%5)==0 && i!=0){
      printf ("|\n");
    }
  }
  printf ("---------------------\n");
  getchar();
}
