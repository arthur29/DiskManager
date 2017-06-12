#include "../estruturas.h"
#include "read.h"

int open (Disk *d , FileIndex **fi , char user[] , char name[]){
  FileIndex current = *fi;
  while (current->next != NULL){
    if (strcmp(current->file_name, name) == 0 && strcmp(current->owner , owner) == 0){
      
      char *pointer = &d[curent->location].block[0]+sizeof(FileHeader);
      if (pointer == d[current->location].block[BLOCK_SIZE - 1]){
        int next_block = d[current->location].next_block_location;
        if (next_block != -1){
          pointer = &d[next_block].block[0];


    }  
    current = current->next;
  }
}
