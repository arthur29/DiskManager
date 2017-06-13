#include "../estruturas.h"
#include "read.h"
#include <string.h>

int open (Disk *d , FileIndex **fi , char user[] , char name[] , char** pointer){
  printf ("OPEN\n");

  FileIndex *current = *fi;
  while (current->next != NULL){
    if (strcmp(current->file_name, name) == 0 && strcmp(current->owner , user) == 0){
      
      *pointer =  &d[current->location].block[0]+sizeof(FileHeader);
      printf ("%li\n",&d[current->location].block[BLOCK_SIZE]);
      if (*pointer == &d[current->location].block[BLOCK_SIZE]){
        int next_block = d[current->location].next_block_location;
        if (next_block != -1){
          *pointer = &d[next_block].block[0];
        }
      }
      return 0;

    }  
    current = current->next;
  }
  return -1;
}
