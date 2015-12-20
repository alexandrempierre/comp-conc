#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NTHREADS 4

#define BROADCAST(threadsDependentes, semaphore) {\
  int i;\
  for (i = 0; i < threadsDependentes; ++i) sem_post(&semaphore);\
}

sem_t mutex, cond;
volatile int t34;

void barreira () {
  sem_wait(&mutex);
  if (++t34 == 2) {
    // sem_post(&cond);
    // sem_post(&cond);

    BROADCAST(2, cond);
  }
  sem_post(&mutex);
}

void *t1 (void *args) {
  printf("olá, tudo bem?\n");

  barreira();

  pthread_exit(NULL);
}

void *t2 (void *args) {
  printf("hello!\n");

  barreira();

  pthread_exit(NULL);
}

void *t3 (void *args) {
  sem_wait(&cond); // espera a execução das threads 1 e 2

  printf("até mais tarde\n");

  pthread_exit(NULL);
}

void *t4 (void *args) {
  sem_wait(&cond); // espera a execução das threads 1 e 2

  printf("tchau!\n");

  pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
  pthread_t threads[NTHREADS];

  t34 = 0;

  sem_init(&cond, 0, 0);
  sem_init(&mutex, 0, 1);

  pthread_create(&threads[0], NULL, t4, NULL);
  pthread_create(&threads[1], NULL, t3, NULL);
  pthread_create(&threads[2], NULL, t1, NULL);
  pthread_create(&threads[3], NULL, t2, NULL);

  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);
  pthread_join(threads[2], NULL);
  pthread_join(threads[3], NULL);

  return 0;
}
