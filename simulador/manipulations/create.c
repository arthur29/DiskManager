#include <string.h>
#include "../estruturas.h"
#include "create.h"

int create (Disk *d , FileIndex **fi , char name[]){
  printf ("CREATE\n");
  
  int i;
  FileIndex *current = (*fi);
  if (current != NULL){
    while (current->next != NULL){
      if (strcmp(current->file_name , name) == 0){
        return -1;
      }
    }
  }
  for (i=0;i<DISK_SIZE;i++){
    if (d[i].in_use != 0){
      FileHeader fh;
      fh.size = sizeof(fh);
      strcpy(fh.owner,"default");
      strcpy(fh.creation,"xx-xx-xxxx");
      strcpy(fh.modification,"xx-xx-xxxx");
      
      char *bytePtr = (char*)&fh;
      char fileHeaderByte[sizeof(fh)];
      memcpy(d[i].block, bytePtr, sizeof(fh));
      
      d[i].in_use = 0;
      d[i].previous_block_location = -1;
      d[i].next_block_location = -1;
      strcpy (d[i].block,fileHeaderByte);

      FileIndex *nfi = malloc (sizeof(FileIndex));
      strcpy(nfi->file_name, name);
      nfi->location = i;
      nfi->next = NULL;
      current = *fi;
      if (current != NULL){
        while (current->next != NULL){
          current = current->next;
        }
        current->next = nfi;
      }else{
        *fi = nfi;
      }
      break; 
    }
  }
  return i;

}

