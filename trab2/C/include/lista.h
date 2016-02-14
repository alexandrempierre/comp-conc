#ifndef H_LISTA
#define H_LISTA

typedef struct estrLista {
  struct estrLista *prox;
  void *info;
} Lista;

/* cria lista vazia */
Lista *listaCriar (void);

/* cria no */
Lista *listaCriarNo (void *info);

/* verifica se a lista esta vazia */
int listaVazia (Lista *l);

/* insere elemento no inicio da lista */
Lista *listaInserir (void *info, Lista *l);

/* busca elemento na lista (retorna NULL se nao for encontrado) */
Lista *listaBuscar (void *info, Lista *l);

/* retira elemento da lista (retorna Lista sem o elemento) */
Lista *listaRetira (void *info, Lista *l);

/* libera memoria usada pela lista */
void listaLiberar (Lista *l);

/* retorna quantidade de elementos na lista */
int listaTamanho (Lista *l);

#endif
