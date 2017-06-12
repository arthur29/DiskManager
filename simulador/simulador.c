#include "estruturas.h"
#include "requisicoes.h"
#include "simulador.h"

void simulador (){

  printf ("SIMULADOR\n");
  Disk disk[100];
  FileIndex *fi = NULL;
  requisicoes ( disk , fi );

}
