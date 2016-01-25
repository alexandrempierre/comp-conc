#include <stdlib.h>
#include "arv.h"

Arvore *arvCriarVazia () {
  return NULL;
}

int arvVazia (Arvore* arv) {
  return arv == NULL;
}

Arvore *arvCriarNo (void *info, Arvore *esq, Arvore *dir) {
  Arvore *no = (Arvore *) malloc(sizeof(Arvore *));
  no->info = info;
  no->esq = esq;
  no->dir = dir;

  return no;
}

Arvore *arvLiberar (Arvore *arv) {
  if (arv != NULL) {
    arvLiberar(arv->esq);
    arvLiberar(arv->dir);
    free(arv);
  }

  return NULL;
}

TipoNo arvTipoNo (Arvore *arv) {
  if (arv == NULL) return VAZIO;
  if (arv->esq == NULL && arv->dir == NULL) return FOLHA;

  return GALHO;
}

int arvSubArvoresVazias (Arvore *arv) {
  if (arv == NULL) return -1;
  return arv->esq == NULL && arv->dir == NULL;
}
