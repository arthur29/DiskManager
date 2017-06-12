#include <string.h>
#include "../estruturas.h"
#include "create.h"

//-1 o arquivo já existe
//-2 o disco está cheio
int create (Disk *d , FileIndex **fi , int *disk_usage , char owner[] , char name[]){
  printf ("CREATE\n");
  
  int i;
  FileIndex *current = (*fi);
  if (current != NULL){
    while (current->next != NULL){
      if (strcmp(current->file_name , name) == 0){
        break;
      }
    }
    if (strcmp(current->file_name , name) == 0){
      return -1;
    }
  }
  for (i=0;i<DISK_SIZE;i++){
    if (disk_usage[i] != 0){
      FileHeader fh;
      fh.size = sizeof(fh);
      strcpy(fh.owner,owner);
      strcpy(fh.creation,"xx-xx-xxxx");
      strcpy(fh.modification,"xx-xx-xxxx");
      
      char *bytePtr = (char*)&fh;
      char fileHeaderByte[sizeof(fh)];
      memcpy(d[i].block, bytePtr, sizeof(fh));
      
      d[i].in_use = 0;
      disk_usage[i] = 0;
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
  if (i == DISK_SIZE){
    return -2;
  }
  return i;

}

