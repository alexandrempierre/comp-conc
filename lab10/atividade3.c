#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NTHREADS 4

sem_t sem;

void *t1 (void *args) {
  printf("olá, tudo bem?\n");
  sem_post(&sem);

  pthread_exit(NULL);
}

void *t2 (void *args) {
  printf("hello!\n");
  sem_post(&sem);

  pthread_exit(NULL);
}

void *t3 (void *args) {
  sem_wait(&sem);
  printf("até mais tarde\n");

  pthread_exit(NULL);
}

void *t4 (void *args) {
  sem_wait(&sem);
  printf("tchau!\n");

  pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
  pthread_t threads[NTHREADS];

  pthread_create(&threads[0], NULL, t4, NULL);
  pthread_create(&threads[1], NULL, t3, NULL);
  pthread_create(&threads[2], NULL, t1, NULL);
  pthread_create(&threads[3], NULL, t2, NULL);

  sem_init(&sem, 0, 0);

  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);
  pthread_join(threads[2], NULL);
  pthread_join(threads[3], NULL);

  return 0;
}
