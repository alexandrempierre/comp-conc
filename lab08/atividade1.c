#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#define TAM_BUFFER  5
#define NTHREADS    2

volatile int buffer[TAM_BUFFER];
volatile int cont_buffer = 0;

pthread_mutex_t mutex;
pthread_cond_t cond;

int fibo (int n) {
  int t0 = 0, t1 = 1;

  for ( ; n > 0; --n) {
    t0 += t1;
    t1 ^= t0 ^= t1 ^= t0;
  }

  return t0;
}

int ehPrimo(long unsigned int n) {
  int i;

  if (n <= 1) return 0;
  if (n == 2) return 1;
  if ( n % 2 == 0) return 0;

  for (i = 3; i < sqrt(n) + 1; i += 2) {
    if (n % i == 0) return 0;
  }

  return 1;
}

void Insere (int item, int in) {
  pthread_mutex_lock(&mutex);

  if (cont_buffer == TAM_BUFFER) pthread_cond_wait(&cond, &mutex);

  buffer[in % 5] = item;
  cont_buffer++;

  pthread_cond_signal(&cond);

  pthread_mutex_unlock(&mutex);
}

int Retira (int out) {
  int item;

  pthread_mutex_lock(&mutex);

  if (cont_buffer == 0) pthread_cond_wait(&cond, &mutex);

  item = buffer[out % 5];
  cont_buffer--;

  pthread_cond_signal(&cond);

  pthread_mutex_unlock(&mutex);

  return item;
}

void * produtor (void * args) {

  int i;
  for (i = 0; i < 25; i++) Insere(fibo(i), i + 1);

  pthread_exit(NULL);
}

void * consumidor (void * args) {
  int i, item;

  for (i = 0; i < 25; i++) {
    item = Retira(i + 1);
    printf("%5d %seh primo\n", item, ehPrimo(item) ? "" : "nao ");
  }

  pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {

  pthread_t threads[NTHREADS];
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cond, NULL);

  pthread_create(&threads[0], NULL, produtor, NULL);
  pthread_create(&threads[1], NULL, consumidor, NULL);

  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);

  pthread_exit(NULL);

  return 0;
}
