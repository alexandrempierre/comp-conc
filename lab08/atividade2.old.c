#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#define TAM_BUFFER    5
#define NTHREADS      3
#define CONSUMIDORES  2
#define PROD_LIMITE   25
#define PBUFFER       printf("%d, %d, %d, %d, %d\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4])

volatile int buffer[TAM_BUFFER];
volatile int cont_buffer = 0;
volatile int out = 1;

pthread_mutex_t mutex;
pthread_cond_t cond_prod;
pthread_cond_t cond_cons;

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

void *produtor (void *args) {
  int i, item;

  for (i = 1; i <= PROD_LIMITE; ++i) {
    item = fibo(i);
    pthread_mutex_lock(&mutex);

    if (cont_buffer == TAM_BUFFER) pthread_cond_wait(&cond_prod, &mutex);

    buffer[i % TAM_BUFFER] = item;
    cont_buffer++;

    pthread_cond_signal(&cond_cons);
    pthread_mutex_unlock(&mutex);
  }

  pthread_exit(NULL);
}

void *consumidor (void *args) {
  int item, fim;

  while (1) {
    pthread_mutex_lock(&mutex);
    fim = out > PROD_LIMITE;
    if (!fim) {
      while (cont_buffer == 0) pthread_cond_wait(&cond_cons, &mutex);

      item = buffer[out++ % TAM_BUFFER];
      cont_buffer--;
    }
    pthread_mutex_unlock(&mutex);
    if (fim) break;
    printf("%2d: %5d %seh primo\n", out-1, item, ehPrimo(item) ? "" : "nao ");
  }

  pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
  int i, item;

  pthread_t threads[NTHREADS];
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cond_prod, NULL);
  pthread_cond_init(&cond_cons, NULL);

  pthread_create(&threads[0], NULL, produtor, NULL);
  pthread_create(&threads[1], NULL, consumidor, NULL);
  pthread_create(&threads[2], NULL, consumidor, NULL);

  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);
  pthread_join(threads[2], NULL);

  // for (i = 0; i <= PROD_LIMITE; i++) {
  //   item = fibo(i);
  //   printf("%2d: %5d %seh primo\n", i, item, ehPrimo(item) ? "" : "nao ");
  // }

  return 0;
}
