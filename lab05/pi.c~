#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h> //para usar a funcao "sysconf"
#include "timer.h"

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

/* Funcoes */
double seriePI (int N) {
  double soma = 0;
  int i;

  for (i = 0; i < N; ++i) {
    soma += TERMO(i);
  }

  return MULT_SERIE * soma;
}

void *seriePIConcorr (void *tid) {
  int i, id = * (int *) tid;
  free(tid);

  double *ret, soma_parcial = 0;

  ret = malloc(sizeof(float));
  TESTE_MALLOC(ret);

  for (i = id; i < N; i+=nThreads) {
    soma_parcial += TERMO(i);
  }

  *ret = soma_parcial;

  pthread_exit((void *) ret);
}

double seriePIIntercalada () {
	double serie = 0, soma_parcial;
	int id, i;
	
	for (id = 0; id < nThreads; ++id) {
		soma_parcial = 0;
		
		for (i = id; i < N; i+=nThreads) {
			soma_parcial += TERMO(i);
		}
		
		serie += soma_parcial;
	}
	
	return MULT_SERIE * serie;
}

/* Funcao principal */
int main(int argc, char const *argv[]) {
  double inicio, fim, tInicializacao, tFinalizacao, tSeq, tConcorr, speedup;
  
  double pi, *retorno;
  int i, numCPU, *tid;

  pthread_t *tid_sistema;
  
  GET_TIME(inicio);

  /* Teste dos argumentos de linha de comando */
  if (argc < 3) {
    printf("Use: %s <numero de elementos da serie> <numero de threads>\n", argv[0]); exit(-1);
  }
  
  numCPU = sysconf(_SC_NPROCESSORS_ONLN);
  //printf("Numero de processadores: %d\n", numCPU);

  N = atoi(argv[1]);
  TESTE_ERRO(N < 1, "o numero de elementos da serie deve ser igual ou maior que 1");

  nThreads = atoi(argv[2]);
  TESTE_ERRO(nThreads < 1, "o numero de threads deve ser igual ou maior que 1");

  if (nThreads > numCPU) {
  	printf("--AVISO: numero de threads maior que o de CPUs\n");
  }
  
  if (nThreads > N) {
  	printf("--AVISO: numero de threads maior que o de elementos da serie\n");
  	printf("-------- algumas threads ficariam ociosas.\n");
  	printf("-------- Mudando numero de threads para correponder ao de elementos da serie\n");
  	nThreads = N;
  }
  
  /* Inicializacoes */
  tid_sistema = malloc(sizeof(pthread_t) * nThreads);
  TESTE_MALLOC(tid_sistema);
  
  retorno = malloc(sizeof(double));
  TESTE_MALLOC(retorno);
  
  pi = 0;
  
  /**/
  GET_TIME(fim);
  
  tInicializacao = fim - inicio;
  
  //printf("Constante:\t%.20f\n", M_PI);

  /* Execucao Sequencial (sem blocos) */
  // pi = seriePI(N);
  //
  // printf("Serie:\t\t%.20f\n", pi);

  /* Execucao Concorrente Intercalada */
  GET_TIME(inicio);
  
  for(i = 0; i < nThreads; ++i) {
    tid = malloc(sizeof(int));
    TESTE_MALLOC(tid);

    if (pthread_create(&tid_sistema[i], NULL, seriePIConcorr, (void *) tid)) {
      printf("--ERRO: pthread_create()"); exit(-1);
    }
  }

  /* Fim da execucao das threads */
  for (i = 0; i < nThreads; ++i) {
    if (pthread_join(tid_sistema[i], (void *) &retorno)) {
      printf("--ERRO: pthread_join()"); exit(-1);
    }

    pi += *retorno;
  }
  
  pi *= MULT_SERIE;
  
  GET_TIME(fim);
  
  tConcorr = fim - inicio;

  //printf("Concorrente: %.20f\n", pi);
  
  /* Execucao Sequencial Intercalada */
  GET_TIME(inicio);
  
  pi = seriePIIntercalada();
  
  //printf("Sequencial:  %.20f\n", pi);
  
  GET_TIME(fim);
  
  tSeq = fim - inicio;
  
  /* Finalizacao */
  GET_TIME(inicio);
  
  free(tid_sistema);
  free(retorno);
  
  GET_TIME(fim);
  
  tFinalizacao = fim - inicio;
  
  tConcorr += tInicializacao + tFinalizacao;
  tSeq += tInicializacao + tFinalizacao;
  
  speedup = tSeq/tConcorr;
  
  printf("Tempo da Funcao Sequencial:\t\t%f\n", tSeq);
  printf("Tempo da Funcao Concorrente:\t\t%f\n", tConcorr);
  printf("Speedup (Sequencial/Concorrente):\t%f\n", speedup);

  return 0;
}

