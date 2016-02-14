#include <stdlib.h>
#include <stdio.h>
#include "fila.h"

/* cria fila vazia */
Fila *filaCriar (void) {
  Fila *f = (Fila *) malloc(sizeof(Fila));
  f->ini = f->fim = NULL;

  return f;
}

/* verifica se a fila esta vazia */
int filaVazia (Fila *f) {
  return listaVazia(f->ini);
}

/* acrescenta elemento ao final da fila */
void filaInserir (void *info, Fila *f) {
  Lista *n = listaCriarNo(info); /* cria no de lista com a informacao */
  n->prox = NULL; /* novo no passa a ser o ultimo */

  if (f->fim != NULL) /* verificar se a fila nao estava vazia */
    f->fim->prox = n;
  else /* fila vazia */
    f->ini = n;

  f->fim = n; /* fim da fila aponta para novo elemento */
}

/* "roda a fila", retira e retorna o primeiro elemento */
void *filaRetirar (Fila *f) {
  Lista *t;
  void *v;

  if (filaVazia(f)) {
    printf("Fila vazia.\n");
    exit(-1);
  }

  t = f->ini;
  v = t->info;
  f->ini = t->prox;
  if (f->ini == NULL) /* verifica se a fila ficou vazia */
    f->fim = NULL;

  free(t);

  return v;
}

/* libera memoria usada pela fila */
void filaLiberar (Fila *f) {
  Lista *q = f->ini;

  listaLiberar(q);
}

/* retorna quantidade de elementos na fila */
int filaTamanho (Fila *f) {
  return listaTamanho(f->ini);
}
