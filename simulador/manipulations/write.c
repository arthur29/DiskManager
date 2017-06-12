#include <string.h>

#include "../estruturas.h"
#include "write.h"


void strcut (char *data,int free_space, int data_size);

int write (Disk *d , FileIndex **fi , int *disk_usage , char current_user[] , char name[] , char data[], int data_size){
  printf ("WRITE\n");
  FileIndex *current = *fi;
  int i;
  if (current != NULL){
    while (current != NULL){
      if (strcmp(current->file_name, name) == 0){
        break;
      }
      current = current->next;
    }
    if (current != NULL){
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
         if (disk_usage[i] != 0){
           count_blocks ++;
           if (count_blocks == qtd_blocks){
             break;
           }
         }
       }
      }
      memcpy(d[current->location].block,&fh,sizeof(fh));
      if (count_blocks == qtd_blocks){
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

        printf ("Escreveu no bloco %d\n",current->location);
        int j;
        for (j=1;j<qtd_blocks;j++){
          for (i=0;i<DISK_SIZE;i++){
            if (disk_usage[i] != 0){
              break;
            }
          }

          d[current->location].next_block_location = i;
          d[i].in_use = 0;
          disk_usage[i] = 0;
          memcpy(d[i].block,data,block);
          char teste[BLOCK_SIZE];
          memcpy(teste,d[i].block,block);
          if (block < data_size){
            strcut(data,block,data_size);
          }else{
            strcpy(data,"");
          } 
          data_size = data_size - block;
          printf ("Escreveu no bloco %d\n",i);
        }
      }

    }else{
      return -1;
    }
  }
  
  return 0;

}
void strcut (char *data,int free_space, int data_size){
  char new_data[data_size];
  int i;
  for (i=free_space; i< data_size;i++){
    new_data[i-free_space] = data[i];
  }
  memcpy(data, new_data, data_size-free_space);
}
