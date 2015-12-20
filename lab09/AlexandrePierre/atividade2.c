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
 * Com prioridade para escrita.
 */

#define N         2   //threads leitoras
#define M         2   //threads escritoras
#define NTHREADS  (N + M)

typedef struct {
  int cont;
  int id;
} estrutura;

volatile estrutura estr;
pthread_mutex_t mutex;
pthread_cond_t cond;
volatile int lendo = 0, escrevendo = 0, filaEscrever = 0;

volatile int continua;

void * escrever (void * tid) {
  int id = * (int *) tid;
  free(tid);

  while (1) {
    pthread_mutex_lock(&mutex);
    continua--;
    filaEscrever++;

    while (lendo || escrevendo)
      pthread_cond_wait(&cond, &mutex);

    escrevendo = 1;

    estr.cont++;
    estr.id = id;

    escrevendo = 0;
    filaEscrever--;

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

    while (filaEscrever || escrevendo && !estr.id)
      pthread_cond_wait(&cond, &mutex);

    lendo = 1;

    estrLocal.cont = estr.cont;
    estrLocal.id = estr.id;

    lendo = 0;

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
  estr.id = 0;

  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cond, NULL);

  //Criacao das threads escritoras
  for (i = 0; i < N; ++i) {
    tid = malloc(sizeof(int));
    *tid = i;
    pthread_create(&threads[*tid], NULL, escrever, (void *) tid);
  }

  //Criacao das threads leitoras
  for (i = 0; i < M; ++i) {
    tid = malloc(sizeof(int));
    *tid = N + i;
    pthread_create(&threads[*tid], NULL, ler, (void *) tid);
  }

  for (i = 0; i < NTHREADS; ++i) {
    pthread_join(threads[i], NULL);
  }

  return 0;
}
