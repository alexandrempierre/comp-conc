/* Prof.: Silvana Rossetto */
/* Introdução ao MPI (biblioteca de troca de mensagens) */
/* Mostra como iniciar e terminar o ambiente de execução no MPI */

/* Compile:  mpicc -o intro0 intro0.c */
/* Run:      mpirun -np <number of processes> ./intro0 */

/* --------------------------------------------------------------------------------------------*/

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int ret;

  //inicia o MPI
  ret = MPI_Init(&argc, &argv); 
  //ret = MPI_Init(NULL, NULL); 

  if (ret == MPI_SUCCESS) {  
    printf ("MPI iniciou corretamente (argc=%d)\n", argc);
  }

  while(argc > 0) {
     printf("argv[%d]=%s\n", argc-1, argv[argc-1]);
     argc--;
  }

  //encerra o MPI
  MPI_Finalize();
  return 0;
}
