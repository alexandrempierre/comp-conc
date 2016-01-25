#ifndef _H_ARV
#define _H_ARV

typedef enum TIPO_NO { VAZIO, GALHO, FOLHA } TipoNo;

typedef struct estrArvoreBinaria {
  void *info;
  struct estrArvoreBinaria *esq, *dir;
} Arvore;

Arvore *arvCriarVazia ();
int arvVazia (Arvore* arv);
Arvore *arvCriarNo (void *conteudo, Arvore *esq, Arvore *dir);
Arvore *arvLiberar (Arvore *arv);
TipoNo arvTipoNo (Arvore *arv);
int arvSubArvoresVazias (Arvore *arv);

#endif
