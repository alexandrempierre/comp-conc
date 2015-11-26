#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Objetivo:
 * Implementar uma “barreira” para sincronizacao das threads de uma aplicacao.
 * Descricao: Implemente um programa concorrente em C com 5 threads. Todas as threads
 * devem executar o mesmo trecho de codigo mostrado abaixo. A cada passo (iteracao), cada
 * thread deve incrementar sua variavel contadora, imprimir o seu ID, o valor da sua variavel
 * contadora e o passo atual, e so podem continuar depois que todas as threads completarem
 * esse passo.
 *
 * Roteiro:
 *
 * 1. Implemente a funcao barreira() para forcar todas as threads a esperar ao final
 * de cada iteracao.
 *
 * 2. Implemente o programa completo e avalie a sua corretude.
 */

/* Condicao logica:
 *
 * Cada thread deve executar um passo da iteracao e ser suspensa ate que todas as
 * threads tenham concluido aquele passo.
 */

#define NTHREADS  5
#define PASSOS    5

/* variaveis globais */
pthread_mutex_t mutex;
pthread_cond_t cond;
volatile int t = 0;

void barreira (int nthreads) {
  pthread_mutex_lock(&mutex);

  if (++t == nthreads) { t = 0; pthread_cond_broadcast(&cond); }
  else { pthread_cond_wait(&cond, &mutex); }

  pthread_mutex_unlock(&mutex);
}

void *A (void *arg) {
  int tid = *(int*)arg, i;
  int cont = 0, boba1, boba2;

  for (i=0; i < PASSOS; i++) {
    cont++;
    printf("Thread %d: cont=%d, passo=%d\n", tid, cont, i);

    //sincronizacao condicional
    barreira(NTHREADS);

    /* faz alguma coisa inutil pra gastar tempo... */
    boba1=100; boba2=-100; while (boba2 < boba1) boba2++;
  }

  pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
  int *tid[NTHREADS], i;
  pthread_t threads[NTHREADS];

  // Inicializacao das variaveis utilizadas na sicronizacao condicional
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cond, NULL);

  // Cria as threads, aloca e define os ids a serem passados como argumento para as threads
  for (i = 0; i < NTHREADS; ++i) {
    if ( (tid[i] = malloc(sizeof(int))) == NULL ) {
      printf("--ERRO: malloc()\n"); exit(-1);
    }

    *tid[i] = i;

    if ( pthread_create(&threads[i], NULL, A, (void *) tid[i]) ) {
      printf("--ERRO: pthread_create()\n"); exit(-1);
    }
  }

  // Aguarda o fim das threads
  for (i = 0; i < NTHREADS; ++i) {
    if ( pthread_join(threads[i], NULL) ) {
      printf("--ERRO: pthread_join()\n"); exit(-1);
    }

    // desaloca os argumentos das threads
    free(tid[i]);
  }

  // desaloca as variaveis usadas na sincronizacao condicional
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond);

  return 0;
}
