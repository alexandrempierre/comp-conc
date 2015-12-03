#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TAM_BUFFER  5

volatile int buffer[TAM_BUFFER];
volatile int cont_buffer = 1;

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
  int i;

  for (i = 1; i <= 25; i++) {
    pthread_mutex_lock(&mutex);
    if (cont_buffer == TAM_BUFFER) {
      pthread_cond_signal(&cond);
      pthread_cond_wait(&cond, &mutex);
    }
    buffer[i % 5] = fibo(i);
    cont_buffer++;
    pthread_mutex_unlock(&mutex);
  }

  pthread_exit(NULL);
}

void * consumidor (void * args) {
  int i;

  for (i = 1; i <= 25; i++) {
    pthread_mutex_lock(&mutex);
    if (cont_buffer == 0) {
      pthread_cond_signal(&cond);
      pthread_cond_wait(&cond, &mutex);
    }
    printf("%sprimo\n", ehPrimo(buffer[i % 5]) ? "eh " : "nao eh ");
    cont_buffer++;
    pthread_mutex_unlock(&mutex);
  }
}

int main(int argc, char const *argv[]) {

  pthread_mutex_init(&mutex);
  pthread_cond_init(&cond);

  printf("%d\n", fibo(atoi(argv[1])));

  return 0;
}
