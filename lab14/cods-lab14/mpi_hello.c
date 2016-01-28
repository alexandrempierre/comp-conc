/* Prof.: Silvana Rossetto */
/* Introdução ao MPI (biblioteca de troca de mensagens em C) */
/* Hello World em MPI */

/* Compile:  mpicc -o mpi_hello mpi_hello.c */
/* Run:      mpirun -np <number of processes> ./mpi_hello */

/* --------------------------------------------------------------------------------------------*/

#include <stddef.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "mpi.h"

int main(int argc, char **argv) {
  char msg1[20], msg2[20];
  int  i, rank, size, tag = 99, tam, tam1, ret;
  MPI_Status status;

  ret = MPI_Init(&argc, &argv);
  if (ret == MPI_SUCCESS){
     MPI_Comm_size (MPI_COMM_WORLD, &size);
     MPI_Comm_rank (MPI_COMM_WORLD, &rank);
     printf ("Sou o processo %d de %d\n", rank, size);
  } else return 1;

  //processo 0
  if (rank == 0) {
    strcpy(msg1, "Hello, world");
    tam = strlen(msg1) + 1; // para incluir o caractere de final de string

    for (i = 1; i < size; i++) {  
       MPI_Send(msg1, tam, MPI_CHAR, i, tag, MPI_COMM_WORLD);  //send assincrono (retorna apos buffer de envio ficar livre)
       //MPI_Ssend(msg1, tam, MPI_CHAR, i, tag, MPI_COMM_WORLD); //send sincrono (retorna apos receptor receber a msg)
       printf( "%d: mensagem enviada para o processo %d: %s\n", rank, i, msg1);
    }
  //demais processos
  } else { 
     MPI_Recv(msg2, 20, MPI_CHAR, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
     MPI_Get_count(&status, MPI_CHAR, &tam1); //descobre o tamanho da mensagem (qtde de elementos do tipo definido)
     printf( "%d: mensagem recebida do processo %d, com tag %d e tamanho %d: %s\n", rank, status.MPI_SOURCE, status.MPI_TAG, tam1, msg2);
  }

  MPI_Finalize();
  return 0;
}
