#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "arv.h"
#include "pilha.h"

Arvore *arv;
Pilha *exec;
int H;

typedef struct estrItemPilha {
  Arvore *arv;
  int h;
} ItemPilha;

void arvImprimir (Arvore *a);
ItemPilha *itemCriar (Arvore *arv, int h);

void processaItem (ItemPilha *item, Arvore **a);

void addProximos (Arvore **arvBin, int h);

int main(int argc, char const *argv[]) {
  Arvore *aux;
  int *val, h = 0;
  ItemPilha *item;

  H = atoi(argv[1]);
  while (H < 2) {
    printf("Digite um numero maior que ou igual a 2\n");
    scanf("%d", &H);
  }

  exec = pilhaCriar();

  val = (int *) malloc(sizeof(int));
  *val = h;
  arv = arvCriarNo((void *) val,
    arvCriarNo(NULL, arvCriarVazia(), arvCriarVazia()),
    arvCriarNo(NULL, arvCriarVazia(), arvCriarVazia())
  );

  /* Incremento que sinaliza para a pilha que os itens empilhados terao altura
   * uma unidade maior que a altura atual
   */
  ++h;

  item = itemCriar(arv->dir, h);
  pilhaInserir(exec, (void *) item);

  item = itemCriar(arv->esq, h);
  pilhaInserir(exec, (void *) item);

  do {
    /* Retira item da pilha de execucao */
    // item = (ItemPilha *) pilhaRetirar(exec);
    // processaItem(item, &aux);
    processaItem((ItemPilha *) pilhaRetirar(exec), &aux);
    h = (*(int *)aux->info) + 1; // proxima altura

    /* Se a condicao de parada ainda nao tiver sido alcancada, ou seja,
     * se a altura do no criado nao tiver chegado ao limite de altura estabelecido
     *
     * Outros nos com alturas maiores devem ser colocados na pilha de execucao
     * para serem criados assim que essa volta do loop terminar
     */
    if (h < H){
      /* Cria um no filho do no atual na arvore e coloca na pilha de execucao
       * para ser processado (direita)
       */
      // aux->dir = arvCriarNo(NULL, arvCriarVazia(), arvCriarVazia());
      // item = itemCriar(aux->dir, h);
      // pilhaInserir(exec, (void *) item);
      //
      // /* Cria um no filho do no atual na arvore e coloca na pilha de execucao
      //  * para ser processado (esquerda)
      //  */
      // aux->esq = arvCriarNo(NULL, arvCriarVazia(), arvCriarVazia());
      // item = itemCriar(aux->esq, h);
      // pilhaInserir(exec, (void *) item);
      addProximos (&aux, h);
    }
  } while (!pilhaVazia(exec));

  arvImprimir(arv);
  printf("\n");

  return 0;
}

void addProximos (Arvore **a, int h) {
  // Arvore *a = *arvBin;
  ItemPilha *item;

  (*a)->dir = arvCriarNo(NULL, arvCriarVazia(), arvCriarVazia());
  item = itemCriar((*a)->dir, h);
  pilhaInserir(exec, (void *) item);

  (*a)->esq = arvCriarNo(NULL, arvCriarVazia(), arvCriarVazia());
  item = itemCriar((*a)->esq, h);
  pilhaInserir(exec, (void *) item);
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

void processaItem (ItemPilha *item, Arvore **a) {
  int *val = (int *) malloc(sizeof(int));

  /* Pegar item da pilha e armazenar em item
   * pegar altura do item e armazenar em val
   * pegar ponteiro do item para arvore e armazenar em a
   * pegar val e armazenar em a->info
   */
  *val = item->h;
  *a = item->arv;
  (*a)->info = (void *) val;
}
