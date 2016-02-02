/* Prof.: Silvana Rossetto */
/* Introdução ao MPI (biblioteca de troca de mensagens em C) */
/* Mostra como trocar mensagens entre DOIS processos */

/* Compile:  mpicc -o intro2 intro2.c */
/* Run:      mpirun -np <number of processes> ./intro2 */

/* --------------------------------------------------------------------------------------------*/

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int numtasks, rank, dest, source, ret, tag = 100;
  char inmsg, outmsg;

  ret = MPI_Init(&argc, &argv);
  if (ret == MPI_SUCCESS){
     MPI_Comm_size (MPI_COMM_WORLD, &numtasks);
     MPI_Comm_rank (MPI_COMM_WORLD, &rank);
     printf ("Sou o processo %d de %d\n", rank, numtasks);
  } else return 1;

  if (numtasks > 1) {
     if (rank == 0) {
       dest = 1; outmsg='x';
       printf("%d: Enviando caractere %c para proc %d\n", rank, outmsg, dest);
       ret = MPI_Send(&outmsg, 1, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
     } else if (rank == 1) {
    //  } else { //todos os outros processos ficarao esperando a mensagem do processo 0, mas apenas o processo 1 a recebera
       source = 0;
       ret = MPI_Recv(&inmsg, 1, MPI_CHAR, source, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
       printf("%d: Recebi o caractere %c do proc %d\n", rank, inmsg, source);
     }
  } else printf("Para executar esse programa é necessário criar pelo menos 2 processos/tarefas!\n");

  MPI_Finalize();
  return 0;
}
