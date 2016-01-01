#ifndef _H_ARV
#define _H_ARV

typedef struct estrArvoreBinaria {
  void *info;
  struct estrArvoreBinaria *esq, *dir;
} Arvore;

Arvore *arvCriarVazia ();
int arvVazia (Arvore* arv);
Arvore *arvCriarNo (void *conteudo, Arvore *esq, Arvore *dir);
Arvore *arvLiberar (Arvore *arv);

#endif
