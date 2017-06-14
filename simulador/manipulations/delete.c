#include "../estruturas.h"
#include "delete.h"
#include <string.h>

//-1 file not found

int delete (Disk *d , FileIndex **fi , int *disk_usage , char file[]){
  system ("clear");
  printf ("DELETE\n");
  FileIndex *current = *fi;

  if (current != NULL){
    while (current != NULL){
      if (strcmp (current->file_name, file) == 0){
        int position = current->location;
        while (position != -1){
          disk_usage[position] = 0;
          d[position].in_use = 0;
          position = d[position].next_block_location;
        }
        return 0;
      }
    }
  }

  return -1;
}
