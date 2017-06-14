#include <string.h>

#include "../estruturas.h"
#include "write.h"


void strcut (char *data,int free_space, int data_size);

//-1 usuário inválido
//-2 arquivo nao encontrado
//-3 disco cheio
int write (Disk *d , FileIndex **fi , int *disk_usage , char current_user[] , char name[] , char data[], int data_size){
  system ("clear");
  printf ("WRITE\n");
  FileIndex *current = *fi;
  
  char data_backup[data_size];

  
  memcpy(data_backup, data, data_size);
  

  int i;
  if (current != NULL){
    while (current != NULL){
      if (strcmp(current->file_name, name) == 0){
        break;
      }
      current = current->next;
    }
    if (current != NULL){
      int position = d[current->location].next_block_location;
      while (position != -1){
        disk_usage[position] = 0;
        d[position].in_use = 0;
        position = d[position].next_block_location;
      }
      char *bytePtr = d[current->location].block;
      FileHeader fh;
      memcpy(&fh , bytePtr , sizeof(fh));
      if (strcmp(fh.owner, current_user) != 0){
        return -1;
      }
      fh.size = sizeof(fh) + data_size;
      strcpy(fh.modification,"yy-yy-yyyy");

      int block = BLOCK_SIZE;
      int free_space = block - sizeof(fh);
      int qtd_blocks = 1;
      if (free_space < data_size){
        qtd_blocks =((data_size - free_space)/block)+1;
        qtd_blocks++;
      }
      int count_blocks = 1;
      if (count_blocks != qtd_blocks){
       for (i=0;i<DISK_SIZE;i++){
         if (disk_usage[i] == 0){
           count_blocks ++;
           if (count_blocks == qtd_blocks){
             break;
           }
         }
       }
      }
      if (count_blocks == qtd_blocks){
        memcpy(d[current->location].block,&fh,sizeof(fh));
        if (free_space < data_size && free_space != 0){
          memcpy(d[current->location].block+sizeof(fh),data,free_space);
          strcut (data, free_space, data_size);
          data_size = data_size - free_space;
        }else{
          if (free_space != 0 ){
            memcpy(d[current->location].block+sizeof(fh),data,data_size);
            strcpy(data,"");
          }
        }

        printf ("Escrita no bloco %d\n", current->location);
        int j;
        int location = current->location;
        int data_size_manipulation = data_size;
        for (j=1;j<qtd_blocks;j++){
          for (i=0;i<DISK_SIZE;i++){
            if (disk_usage[i] == 0){
              break;
            }
          }
          
          d[location].next_block_location = i;
          
          if (j == qtd_blocks-1){
            d[i].next_block_location = -1;
          }
          
          d[i].in_use = 1;
          disk_usage[i] = 1;
          memcpy(d[i].block,data,block);
          if (block < data_size_manipulation){
            strcut(data,block,data_size);
            data_size_manipulation = data_size_manipulation - block;
          }else{
            strcpy(data,"");
            data_size_manipulation = 0;
          }
          location = i;
          printf ("Escrita no bloco %d\n", i);
        }
      }else{
        return -3;
      }
      memcpy(data, data_backup,data_size);
      return i;
    }else{
      strcpy(data, data_backup);
      return -2;
    }
  }
  
  strcpy(data,data_backup);
  return -1;

}
void strcut (char *data,int free_space, int data_size){
  char new_data[data_size];
  int i;
  for (i=free_space; i< data_size;i++){
    new_data[i-free_space] = data[i];
  }
  memcpy(data, new_data, data_size-free_space);
}
