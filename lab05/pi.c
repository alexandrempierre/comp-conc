#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h> //para usar a funcao "sysconf"

/* Constantes e Macros */
#define TESTE_ERRO(condicao_erro, msg) {\
  if(condicao_erro) {\
    printf("--ERRO: %s\n", msg); exit(-1);\
  }\
}
#define TESTE_MALLOC(ptr) TESTE_ERRO(ptr == NULL, "malloc()")
#define MULT_SERIE 4
#define NUM(i) (1.0 - i % 2 * 2.0)
#define DEN(i) (2.0*i + 1.0)
#define TERMO(i) NUM(i)/DEN(i)

/* Variaveis globais */
int nThreads, N;
int resto;
int tamBloco;

/* Funcoes */
double seriePI (int N) {
  double soma = 0;
  int i;

  for (i = 0; i < N; ++i) {
    soma += TERMO(i);
  }

  return MULT_SERIE * soma;
}

void * seriePIConcorr (void * tid) {
  int i, id = * (int *) tid;
  free(tid);

  double *ret, soma_parcial = 0;

  ret = malloc(sizeof(float));
  TESTE_MALLOC(ret);

  for (i = id; i < N; i+= nThreads) {
    soma_parcial += TERMO(i);
  }

  *ret = soma_parcial;

  pthread_exit((void *) ret);
}

/* Funcao principal */
int main(int argc, char const *argv[]) {
  double pi, *retorno;
  int i, numCPU, *tid;

  pthread_t *tid_sistema;

  /* Teste dos argumentos de linha de comando */
  if (argc < 3) {
    printf("Use: %s <numero de elementos da serie> <numero de threads>\n", argv[0]); exit(-1);
  }

  N = atoi(argv[1]);
  TESTE_ERRO(N < 1, "o numero de elementos da serie deve ser igual ou maior que 1");

  nThreads = atoi(argv[2]);
  TESTE_ERRO(nThreads < 1, "o numero de threads deve ser igual ou maior que 1");

  numCPU = sysconf(_SC_NPROCESSORS_ONLN);

  if (nThreads > numCPU) {
    /* code */
  }

  /* Execucao Sequencial (sem blocos) */
  // pi = seriePI(N);
  //
  printf("Constante:\t%.20f\n", M_PI);
  // printf("Serie:\t\t%.20f\n", pi);

  /* Execucao Concorrente em Blocos */
  /* Criacao das threads */
  tid_sistema = malloc(sizeof(pthread_t) * nThreads);
  TESTE_MALLOC(tid_sistema);

  for(i = 0; i < nThreads; ++i) {
    tid = malloc(sizeof(int));
    TESTE_MALLOC(tid);

    if (pthread_create(&tid_sistema[i], NULL, seriePIConcorr, (void *) tid)) {
      printf("--ERRO: pthread_create()"); exit(-1);
    }
  }

  pi = 0;

  /* Fim da execucao das threads */
  for (i = 0; i < nThreads; ++i) {
    if (pthread_join(tid_sistema[i], (void *) &retorno)) {
      printf("--ERRO: pthread_join()"); exit(-1);
    }

    pi += *retorno;
  }

  free(tid_sistema);
  pi *= MULT_SERIE;

  printf("Concorrente: %.20f\n", pi);

  return 0;
}
