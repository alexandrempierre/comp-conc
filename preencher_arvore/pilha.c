#include <stdlib.h>
#include "pilha.h"

int pilhaVazia (Pilha *p) {
  return p == NULL || p->no == NULL;
}

Pilha *pilhaCriar (void) {
  Pilha *p = (Pilha *) malloc(sizeof(Pilha));
  p->no = NULL;

  return p;
}

void pilhaInserir (Pilha *p, void *info) {
  Lista *l = (Lista *) malloc(sizeof(Lista));
  l->info = info;
  l->prox = p->no;
  p->no = l;
}

void *pilhaRetirar (Pilha *p) {
  if (p == NULL || p->no == NULL) return NULL;

  Lista *l = p->no;
  void *info = l->info;

  p->no = l->prox;
  free(l);

  return info;
}
