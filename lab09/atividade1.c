#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Roteiro:
 *
 * Implemente uma aplicacao em C com uma variavel global compartilhada que
 * possui dois campos (struct): um contador (inteiro) e um identificador de
 * thread (inteiro). O conteudo dessa variavel sera lido por threads leitoras
 * e escrito/alterado por threads escritoras.
 *
 * As threads escritoras alteram a variavel incrementando o valor do contador
 * e armazenando o seu ID (identificador da thread) no outro campo da estrutura.
 *
 * As threads leitoras leem o valor da variavel (os dois campos) e o armazenam
 * em uma variavel local. Depois imprimem esse valor e voltam a solicitar nova
 * leitura.
 *
 * Nessa minha versão, toda vez que o valor da estrutura so pode ser alterado
 * apos ser lido por todas as threads leitoras e cada leitora soh vai ler cada
 * valor uma unica vez
 */

#define N         20   //threads leitoras
#define M         200   //threads escritoras
#define NTHREADS  (N + M)
#define PRI_ESCR  estr.id == -1

typedef struct {
  int cont;
  int id;
} estrutura;

volatile estrutura estr;
pthread_mutex_t mutex;
pthread_cond_t cond;
volatile int lendo = 0, escrevendo = 0, filaEscrever = 0;
volatile int lido[N];

volatile int continua;

int todasLeram () {
  int res = 1, i;
  for (i = 0; i < N; ++i)
    res &= lido[i];

  return res;
}

void zeraLido () {
  int i;
  for (i = 0; i < N; ++i)
    lido[i] = 0;
}

void * escrever (void * tid) {
  int id = * (int *) tid;
  free(tid);

  while (1) {
    pthread_mutex_lock(&mutex);
    printf("Thread %d (escritora) iniciada\n", id);

    while (lendo || escrevendo || !(todasLeram() || PRI_ESCR))
      pthread_cond_wait(&cond, &mutex);

    escrevendo = 1;

    estr.cont++;
    estr.id = id;

    escrevendo = 0;
    zeraLido();

    pthread_cond_broadcast(&cond);

    printf("Thread %d escrevendo\n", id);
    pthread_mutex_unlock(&mutex);
  }

  pthread_exit(NULL);
}

void * ler (void * tid) {
  int id = * (int *) tid;
  free(tid);
  estrutura estrLocal;

  while (1) {
    pthread_mutex_lock(&mutex);
    printf("Thread %d (leitora) iniciada\n", id);

    while (lido[id] || escrevendo) {
      pthread_cond_wait(&cond, &mutex);
    }

    lendo = 1;

    estrLocal.cont = estr.cont;
    estrLocal.id = estr.id;

    lendo = 0;
    lido[id] = 1;

    pthread_cond_broadcast(&cond);

    printf("Thread %d (leitora) - id: %d - cont: %d\n", id, estrLocal.id, estrLocal.cont);
    pthread_mutex_unlock(&mutex);
  }

  pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
  // Incializacoes
  pthread_t threads[NTHREADS];
  int i, *tid;
  estr.cont = 0;
  estr.id = -1;

  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cond, NULL);

  for (i = 0; i < N; ++i)
    lido[i] = 1;


  //Criacao das threads leitoras
  for (i = 0; i < M; ++i) {
    tid = malloc(sizeof(int));
    *tid = i;
    pthread_create(&threads[*tid], NULL, ler, (void *) tid);
  }

  //Criacao das threads escritoras
  for (i = 0; i < N; ++i) {
    tid = malloc(sizeof(int));
    *tid = M + i;
    pthread_create(&threads[*tid], NULL, escrever, (void *) tid);
  }

  for (i = 0; i < NTHREADS; ++i) {
    pthread_join(threads[i], NULL);
  }

  return 0;
}
