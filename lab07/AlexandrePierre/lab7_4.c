#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Condicao logica:
 *
 * As threads 1 e 2 devem ser executadas antes das threads 3 e 4, a ordem de
 * execucao entre 1 e 2 nao importa, assim como tambem nao importa entre 3 e 4
 */

/* Observacoes:
 *
 * Nesse programa nao e necessario usar uma estrutura de repeticao para checar a
 * condicao logica porque a variavel que representa a condicao so existe para
 * dizer se as threads 3 e 4 devem (t34 = 2) ou nao (t34 < 2) ser desbloqueadas,
 * t34 nao muda depois de assumir valor igual a 2
 */

#define NTHREADS 4

/* Declaracao das variaveis globais necessarias para a implementar a sincronizacao condicional */
pthread_mutex_t mutex;
pthread_cond_t cond34;
volatile int t34 = 0; // Variavel cujo valor vai determinar a execucao das threads 3 e 4

/* Funcoes das threads */
void *T1 (void * tid) {
  printf("tudo bem?\n");

  pthread_mutex_lock(&mutex);
  t34++;
  if(t34 == 2) { pthread_cond_broadcast(&cond34); }
  pthread_mutex_unlock(&mutex);

  pthread_exit(NULL);
}

void *T2 (void * tid) {
  printf("hola!\n");

  pthread_mutex_lock(&mutex);
  t34++;
  if(t34 == 2) { pthread_cond_broadcast(&cond34); }
  pthread_mutex_unlock(&mutex);

  pthread_exit(NULL);
}

void *T3 (void * tid) {
  pthread_mutex_lock(&mutex);
  if (t34 != 2) { pthread_cond_wait(&cond34, &mutex); }
  pthread_mutex_unlock(&mutex);

  printf("ate mais tarde.\n");

  pthread_exit(NULL);
}

void *T4 (void * tid) {
  pthread_mutex_lock(&mutex);
  if (t34 != 2) { pthread_cond_wait(&cond34, &mutex); }
  pthread_mutex_unlock(&mutex);

  printf("tchau!\n");

  pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
  void *T[NTHREADS]; // vetor de funcoes (para usar estruturas de repeticao)
  pthread_t threads[NTHREADS];

  int i;

  /* Inicializacao dos ponteiros para as funcoes e dos argumentos das threads */
  for (i = 0; i < NTHREADS; ++i) {
    if ( (T[i] = malloc(sizeof(void))) == NULL ) {
      printf("--ERRO: malloc()\n"); exit(-1);
    }
  }

  /* Funcoes colocadas num vetor de ponteiros para void */
  T[0] = T1, T[1] = T2, T[2] = T3, T[3] = T4;

  /* Inicializacao das variaveis necessarias para a sincronizacao condicional */
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cond34, NULL);

  /* Cria threads */
  for (i = 0; i < NTHREADS; ++i) {
    if ( pthread_create(&threads[i], NULL, T[i], NULL) ) {
      printf("--ERRO: pthread_create()\n"); exit(-1);
    }
  }

  /* Aguarda o fim das threads */
  for (i = 0; i < NTHREADS; ++i) {
    if ( pthread_join(threads[i], NULL) ) {
      printf("--ERRO: pthread_join()\n"); exit(-1);
    }
  }

  /* Desaloca memoria das variaveis usadas na sicronizacao condicional */
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond34);

  return 0;
}
