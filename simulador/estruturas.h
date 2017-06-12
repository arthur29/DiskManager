#include <stdio.h>
#include <stdlib.h>


//previous_block_location and next_block_location < 0 quando não tem

typedef struct Disks {

  int in_use;                       //0 para usando != 0 para não em uso
  int previous_block_location;      //para voltar
  int next_block_location;          //para avancar no "disco"
  char block[1000];                 //bloco de dados

} Disk;

typedef struct FileHeaders {
  
  int size;                         //tamanho do arquivo
  int protection;                   //Campo para protecao do arquivo
  char owner[100];                  //Dono do arquivo
  char creation[9];                 //Data de criação
  char modification[9];             //Data de modificacao

} FileHeader;

typedef struct FileIndex {

  char file_name[100];
  int location;

} FileIndex;
