/* Prof.: Silvana Rossetto */
/* Introdução ao MPI (biblioteca de troca de mensagens em C) */
/* Mostra como identificar os processos de um grupo */

/* Compile:  mpicc -o intro1 intro1.c */
/* Run:      mpirun -np <number of processes> ./intro1 */

/* --------------------------------------------------------------------------------------------*/

#include "mpi.h"
#include <stdio.h>

int main(int argc, char **argv) {
  int numtasks, rank, ret;

  ret = MPI_Init(&argc, &argv);

  if (ret == MPI_SUCCESS){
     MPI_Comm_size(MPI_COMM_WORLD, &numtasks); //obtem o numero de processos dentro do grupo
     MPI_Comm_rank(MPI_COMM_WORLD, &rank); //obtem o identificador do processo dentro do grupo
     printf ("Sou o processo %d de %d\n", rank, numtasks);
  }

  MPI_Finalize(); 
  return 0;
}
