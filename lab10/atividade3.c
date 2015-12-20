#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NTHREADS 4

#define BROADCAST(threadsDependentes, semaphore) {\
  int i;\
  for (i = 0; i < threadsDependentes; ++i) sem_post(&semaphore);\
}

sem_t t1_ok, t2_ok;

void *t1 (void *args) {
  printf("olá, tudo bem?\n");

  // sem_post(&t1_ok); // envia o sinal de que a thread 1 já foi executada
  // sem_post(&t1_ok); // envia o sinal de que a thread 1 já foi executada

  /* O sinal é enviado duas vezes para que não seja necessário liberar o
   * semáforo dentro de uma das threads dependentes (threads 3 e 4).
   *
   * O funcionamento vai ser muito parecido com o broadcast da sincronização
   * condicional.
   *
   * Criei a macro BROADCAST para ilustrar o quão parecido seria.
   */

   BROADCAST(2, t1_ok);

  pthread_exit(NULL);
}

void *t2 (void *args) {
  printf("hello!\n");

  // sem_post(&t2_ok); // envia o sinal de que a thread 2 já foi executada
  // sem_post(&t2_ok); // envia o sinal de que a thread 2 já foi executada

  BROADCAST(2, t2_ok); // explicações no código da thread 1

  pthread_exit(NULL);
}

void *t3 (void *args) {
  sem_wait(&t1_ok); // espera a execução da thread 1
  sem_wait(&t2_ok); // espera a execução da thread 2

  printf("até mais tarde\n");

  pthread_exit(NULL);
}

void *t4 (void *args) {
  sem_wait(&t1_ok); // espera a execução da thread 1
  sem_wait(&t2_ok); // espera a execução da thread 2

  printf("tchau!\n");

  pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
  pthread_t threads[NTHREADS];

  sem_init(&t1_ok, 0, 0);
  sem_init(&t2_ok, 0, 0);

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
