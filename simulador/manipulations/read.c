#include "../estruturas.h"
#include "read.h"
#include <string.h>


// -1 arquivo do usuario não encontrado


int read (Disk *d , FileIndex **fi , char current_user[] , char name[] , char **block){
 printf ("READ\n");
  
  FileIndex *current = *fi;
  while (current != NULL){
    if (strcmp (current->file_name, name) == 0 && strcmp (current->owner, current_user) == 0){
      FileHeader fh;
      memcpy (&fh, d[current->location].block,sizeof(fh));
      
      int size = fh.size - sizeof(fh);
      char *data = (char*) malloc (size);
      *block = data;
      int data_index = 0;
      int partial_block = BLOCK_SIZE;
      
      partial_block -= sizeof(fh);
      char data_aux[BLOCK_SIZE];
      int block_size = BLOCK_SIZE;
      if ( partial_block > 0 ){
        int i;
        for (i=sizeof(fh)+1;i<BLOCK_SIZE; i++){
          data_aux[i-sizeof(fh)-1] = d[current->location].block[i];
        }
        memcpy(data,data_aux,(block_size-(sizeof(fh))));
        data_index += (block_size-(sizeof(fh)));
        size -=(block_size-(sizeof(fh)+1));
      }
      if (d[current->location].next_block_location != -1){
        int position = d[current->location].next_block_location;
        while (position != -1){
          if (size > block_size){
            memcpy(data+data_index,d[position].block,block_size);
            data_index +=block_size;
            size -=block_size;
          }else{
            if (size>0){
              memcpy(data+data_index,d[position].block,size-1);
              data_index+=size;
              data[data_index] = '\0';
              data_index++;
              size -= size;
            }
          }
          position = d[position].next_block_location;
        }
      }
      return 0;
    }
    current = current->next;
  }
  
  return -1;
}
