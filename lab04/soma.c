#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> //para usar a funcao "sysconf"

// Objetivo:
// Implementar um algoritmo concorrente para somar todos os elementos de um
// vetor de floats e imprimir o resultado na saıda padrao.

int N, nthreads;
float *vetor;

void * somaElementos (void * tid) {
  int id = * (int *) tid;
  free(tid);

  float soma, *ret;
  int i;

  ret = (float *) malloc(sizeof(float));

  soma = 0;
  for (i = id; i < N; i += nthreads) {
    soma += vetor[i];
  }

  *ret = soma;

  pthread_exit((void *) ret);
}

float somaSequencial () {
  float soma = 0;
  int i;

  for (i = 0; i < N; i++) {
    soma += vetor[i];
  }

  return soma;
}

float somaSequencialIntercalada () {
  float soma = 0, soma_thread;
  int i, j;

  for (i = 0; i < nthreads; i++) {
    soma_thread = 0;

    for (j = i; j < N; j += nthreads) {
      soma_thread += vetor[j];
    }

    soma += soma_thread;
  }

  return soma;
}

int main(int argc, char const *argv[]) {

  if (argc != 3) {
    printf("Use: %s <arquivo de entrada> <numero de threads>\n", argv[0]); exit(-1);
  }

  FILE *arquivo;
  int numCPU, i;

  pthread_t *tid_sistema;
  int *tid;
  float soma, *retorno;

  /* Abrir arquivo com dados */
  arquivo = fopen(argv[1], "r");
  if (arquivo == (FILE *) NULL) {
    printf("--ERRO: fopen()\n"); exit(-1);
  }

  /* Ler tamanho do vetor */
  if ( fscanf(arquivo, "%d", &N) != 1 ) {
    printf("--ERRO: fscanf()\n"); exit(-1);
  }

  /* Ler numero de threads */
  nthreads = atoi(argv[2]);
  numCPU = sysconf(_SC_NPROCESSORS_ONLN);

  if (nthreads > numCPU) nthreads = numCPU;
  else if (nthreads > N) nthreads = N;
  else if (nthreads < 1) nthreads = 1;

  /* Alocar vetor na memoria */
  vetor = malloc(N * sizeof(float));
  if (vetor == NULL) {
    printf("--ERRO: malloc()\n"); exit(-1);
  }

  /* Preencher elementos do vetor */
  for (i = 0; i < N; i++) {
    if ( !fscanf(arquivo, "%f", &vetor[i]) ) {
      printf("--ERRO: fscanf()\n"); exit(-1);
    }
  }

  /* Criar vetor de threads */
  tid_sistema = (pthread_t *) malloc(nthreads * sizeof(pthread_t));
  if (tid_sistema == NULL) {
    printf("--ERRO: malloc()\n"); exit(-1);
  }

  /* Somar elementos do vetor */
  for (i = 0; i < nthreads; i++) {
    tid = malloc(sizeof(int));
    if (tid == NULL) {
      printf("--ERRO: malloc()\n"); exit(-1);
    }

    *tid = i;
    if ( pthread_create(&tid_sistema[i], NULL, somaElementos, (void *) tid) ) {
      printf("--ERRO: pthread_create()\n"); exit(-1);
    }
  }

  retorno = (float *) malloc(sizeof(float));
  soma = 0;

  for (i = 0; i < nthreads; i++) {
    if ( pthread_join(tid_sistema[i], (void *) &retorno) ) {
      printf("--ERRO: pthread_join()\n"); exit(-1);
    }

    soma += *retorno;
  }

  printf("Soma sequencial:\t\t %.8f\n", somaSequencial());
  printf("Soma concorrente:\t\t %.8f\n", soma);
  printf("Soma sequencial intercalada:\t %.8f\n", somaSequencialIntercalada());

  printf("\n");
  return 0;
}
