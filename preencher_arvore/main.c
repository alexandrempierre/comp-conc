#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "arv.h"
#include "pilha.h"

Arvore *arv;
Pilha *exec;
int H, nThreads, *loopCont;

pthread_mutex_t mutex;
pthread_cond_t cond;

typedef struct estrItemPilha {
  Arvore *arv;
  int h;
} ItemPilha;

void arvImprimir (Arvore *a);
ItemPilha *itemCriar (Arvore *arv, int h);

void processaItem (ItemPilha *item, Arvore **a);

void addProximos (Arvore **arvBin, int h);

int parar (int tid) {
  int para = 0, i;
  for (i = 0; i < nThreads; i++) para = loopCont[i] < loopCont[tid] || para;

  return para;
}

void barreira (int tid) {
  int i, p = parar(tid);
  pthread_mutex_lock(&mutex);
  while (p) {
    pthread_cond_broadcast(&cond);
    pthread_cond_wait(&cond, &mutex);
    p = parar(tid);
  }
  pthread_mutex_unlock(&mutex);
}

void *t (void *args) {
  Arvore *aux;
  int *val, h, tid = * (int *) args;
  ItemPilha *item;

  while (1) {
    barreira(tid);
    pthread_mutex_lock(&mutex);
    if (pilhaVazia(exec)) break;
    item = (ItemPilha *) pilhaRetirar(exec);
    pthread_mutex_unlock(&mutex);

    processaItem(item, &aux);
    h = (*(int *)aux->info) + 1;

    if (h < H){
      addProximos (&aux, h);
    }

    loopCont[tid]++;
  }

  pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
  Arvore *aux;
  int *val, h = 0;
  ItemPilha *item;

  H = atoi(argv[1]);
  nThreads = atoi(argv[2]);

  {
    exec = pilhaCriar();

    val = (int *) malloc(sizeof(int));
    *val = h;
    arv = arvCriarNo((void *) val,
      arvCriarNo(NULL, arvCriarVazia(), arvCriarVazia()),
      arvCriarNo(NULL, arvCriarVazia(), arvCriarVazia())
    );
    ++h;

    item = itemCriar(arv->dir, h);
    pilhaInserir(exec, (void *) item);

    item = itemCriar(arv->esq, h);
    pilhaInserir(exec, (void *) item);
  }

  pthread_t *threads = malloc(sizeof(pthread_t) * nThreads);
  pthread_mutex_init(&mutex, NULL);
  loopCont = malloc(sizeof(int) * nThreads);

  int i;
  for (i = 0; i < nThreads; i++) loopCont[i] = 0;

  int *tid;
  for (i = 0; i < nThreads; i++) {
    tid = (int *) malloc(sizeof(int));
    *tid = i;
    pthread_create(&threads[i], NULL, t, (void *) tid);
  }
  for (i = 0; i < nThreads; i++) pthread_join(threads[i], NULL);

  arvImprimir(arv);
  printf("\n");

  return 0;
}

void addProximos (Arvore **a, int h) {
  ItemPilha *item;

  (*a)->dir = arvCriarNo(NULL, arvCriarVazia(), arvCriarVazia());
  item = itemCriar((*a)->dir, h);

  pthread_mutex_lock(&mutex);
  pilhaInserir(exec, (void *) item);
  pthread_mutex_unlock(&mutex);

  (*a)->esq = arvCriarNo(NULL, arvCriarVazia(), arvCriarVazia());
  item = itemCriar((*a)->esq, h);

  pthread_mutex_lock(&mutex);
  pilhaInserir(exec, (void *) item);
  pthread_mutex_unlock(&mutex);
}

void processaItem (ItemPilha *item, Arvore **a) {
  int *val = (int *) malloc(sizeof(int));

  *val = item->h;
  *a = item->arv;
  (*a)->info = (void *) val;
}

void arvImprimir (Arvore *a) {
  int info;
  printf("<");
  if (!arvVazia(a)){
    info = * (int *) a->info;
    printf("%d", info);
    arvImprimir(a->esq);
    arvImprimir(a->dir);
  }
  printf(">");
}

ItemPilha *itemCriar (Arvore *arv, int h) {
  ItemPilha *i = (ItemPilha *) malloc(sizeof(ItemPilha));
  *i = (ItemPilha){arv, h};

  return i;
}
