#include "simulador.h"
#include "estruturas.h"
#include "requisicoes.h"

void simulador (){

  Disk disk[100];
  FileIndex *fi = NULL;
  int open (Disk *disk , FileIndex *fi , char *name){
	while (fi->next != null){
		if (fi->name == name)
			return fi->location;
		}
	}
	return -1;
  }
  requisicoes ( &disk , fi );

}
