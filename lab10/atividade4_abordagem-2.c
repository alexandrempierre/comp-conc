#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define TAM_BUFFER  5
#define NTHREADS    8
#define NPROD       7
#define NCONS       1

volatile int buffer[TAM_BUFFER] = {-1, -1, -1, -1, -1};

sem_t semVazio, semCheio, *mutex;
volatile int poe[NPROD], tira[NCONS], posTira, cont;

void insere (int n) {
  buffer[posPoe++] = n;
  posPoe %= TAM_BUFFER;
}

int retira () {
  int saida = buffer[posTira];

  buffer[posTira++] = -1;
  posTira %= TAM_BUFFER;

  return saida;
}

void printBuffer () {
  int i;

  printf("buffer - { ");
  for (i = 0; i < TAM_BUFFER; ++i) {
    printf("%d", buffer[i]);
    if(i < TAM_BUFFER - 1) printf(", ");
  }
  printf(" }\n");
}

void * produtor (void * args) {
  int id = * (int *) args, i;
  free(args);

  while (1) {
    sem_wait(&semVazio);

    sem_wait(&mutex);
    insere(id);
    printBuffer();
    sem_post(&mutex);

    sem_post(&semCheio);
  }

  pthread_exit(NULL);
}

void * consumidor (void * args) {
  int item;

  while (1) {
    sem_wait(&semCheio);

    sem_wait(&mutex);
    item = retira();
    printf("item retirado: %d\n", item);
    printBuffer();
    sem_post(&mutex);

    sem_post(&semVazio);
  }

  pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
  pthread_t threads[NTHREADS];
  int i, *tid;

  posPoe = 0, posTira = 0, cont = 0;
  sem_init(&semVazio, 0, TAM_BUFFER);
  sem_init(&semCheio, 0, 0);

  mutex = malloc(TAM_BUFFER * sizeof(sem_t));
  for (i = 0; i < TAM_BUFFER; ++i) {
      sem_init(mutex[i]);
  }

  //cria threads consumidoras
  for (i = 0; i < NCONS; ++i) {
    pthread_create(&threads[i], NULL, consumidor, NULL);
  }

  // cria threads produtoras
  for (i = NCONS; i < NTHREADS; ++i) {
    tid = malloc(sizeof(int));
    *tid = i;
    pthread_create(&threads[i], NULL, produtor, (void *) tid);
  }

  // aguarda o fim da execução das threads
  for (i = 0; i < NTHREADS; ++i) {
    pthread_join(threads[i], NULL);
  }

  return 0;
}
