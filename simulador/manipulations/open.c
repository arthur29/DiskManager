#include "../estruturas.h"
#include "read.h"
#include <string.h>

//type == 0 é pra escrita
//type == 1 é pra leitura

int open (Disk *d , FileIndex **fi , char user[] , char name[] , int type , char **pointer){
  system ("clear");
  printf ("OPEN\n");

  FileIndex *current = *fi;
  int block_size = BLOCK_SIZE;
  while (current->next != NULL){
    if (strcmp(current->file_name, name) == 0 && strcmp(current->owner , user) == 0){

      int position = current->location;
      if (type == 0){
        FileHeader fh;
        memcpy (&fh, d[current->location].block, sizeof(FileHeader));
        int bytes = fh.size;
        while (d[position].next_block_location != -1){
          position = d[position].next_block_location;
          bytes = bytes - block_size;
        }
        *pointer = d[position].block+bytes;  
      }else{
        if (block_size > sizeof(FileHeader)){
          *pointer = d[position].block+sizeof(FileHeader);
        }else{
          if (d[position].next_block_location != -1){
            position = d[position].next_block_location;
            *pointer = d[position].block+sizeof(FileHeader);
          }
        printf ("%li\n", *pointer);
        }
      }
      return 0;
    }  
    current = current->next;
  }
  return -1;
}
