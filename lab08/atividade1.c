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

void * produtor (void * args) {
  int i, n;

  for (i = 1; i <= 25; i++) {
    n = fibo(i);

    pthread_mutex_lock(&mutex);

    if (cont_buffer > 0) { pthread_cond_signal(&cond); }
    if (cont_buffer == TAM_BUFFER) { pthread_cond_wait(&cond, &mutex); }

    buffer[i % 5] = n;
    cont_buffer++;

    pthread_mutex_unlock(&mutex);
  }

  pthread_exit(NULL);
}

void * consumidor (void * args) {
  int i, n;

  for (i = 1; i <= 25; i++) {
    pthread_mutex_lock(&mutex);

    if (cont_buffer < TAM_BUFFER) { pthread_cond_signal(&cond); }
    if (cont_buffer == 0) { pthread_cond_wait(&cond, &mutex); }

    n = buffer[i % 5];
    cont_buffer--;

    pthread_mutex_unlock(&mutex);

    printf("%5d %seh primo\n", n, ehPrimo(n) ? "" : "nao ");
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

  // int i;
  // for (i = 1; i <= 25; i++) {
  //   printf("%2d: %5d: %seh primo\n", i, fibo(i), ehPrimo(fibo(i)) ? "" : "nao ");
  // }

  pthread_exit(NULL);

  return 0;
}
