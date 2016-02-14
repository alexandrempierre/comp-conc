#include <stdlib.h>
#include "lista.h"

Lista *listaCriar (void) { /* cria lista vazia */
  return NULL;
}

Lista *listaCriarNo (void *info) { /* cria no de lista isoladamente */
  Lista *novo = (Lista *) malloc(sizeof(Lista)); /* aloca memoria */
  novo->info = info;
  novo->prox = NULL;

  return novo;
}

int listaVazia (Lista *l) { /* verifica se a lista esta vazia */
  return (l == NULL);
}

// Adicionar elemento no inicio da lista
Lista *listaInserir (void *info, Lista *l) {
  Lista *novo = listaCriarNo(info);
  novo->prox = l;

  return novo;
}

Lista *listaBuscar (void *info, Lista *l) { /* busca elemento na lista */
  Lista *p;

  /* percorre lista ate o ponteiro ser nulo */
  for (p = l; p != NULL; p = p->prox)
    if (p->info == info) /* retorna no da lista se elemento for encontrado */
      return p;

  return NULL;
}

Lista *listaRetira (void *info, Lista *l) {
  Lista *ant = NULL; /* ponteiro para o elemento anterior */
  Lista *p = l; /* ponteiro para percorrer a lista */

  /* Procura elemento na lista, guardando anterior */
  while (p != NULL && p->info != info) {
    ant = p;
    p = p->prox;
  }

  /* verifica se achou elemento */
  if (p == NULL) return l; /* retorna lista original caso nao encontre */

  /* retira elemento */
  if (ant == NULL) l = p->prox; /* retirada do elemento caso esteja no inicio */
  else ant->prox = p->prox; /* retirada do elemento caso esteja no meio */

  return l;
}

/* libera memoria alocada para a lista */
void listaLiberar (Lista *l) {
  Lista *p = l;

  while (p != NULL) {
    Lista *t = p->prox; /* guarda ponteiro para o proximo elemento */
    free(p); /* libera memoria apontada por p */
    p = t; /* faz p apontar para o proximo elemento */
  }
}

/* retorna quantidade de elementos na lista */
int listaTamanho (Lista *l) {
  Lista *p;
  int tamanho = 0;

  for (p = l; p != NULL; p = p->prox) tamanho++;

  return tamanho;
}
