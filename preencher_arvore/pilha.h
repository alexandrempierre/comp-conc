#ifndef _H_PILHA
#define _H_PILHA

typedef struct estrLista {
  void *info;
  struct estrLista *prox;
} Lista;

typedef struct estrPilha {
  Lista *no;
} Pilha;

int pilhaVazia (Pilha *p);
Pilha *pilhaCriar (void);
void pilhaInserir (Pilha *p, void *info);
void *pilhaRetirar (Pilha *p);

#endif
