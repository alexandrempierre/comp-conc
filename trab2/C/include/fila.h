#ifndef H_FILA
#define H_FILA

#include "lista.h"

typedef struct estrFila {
  Lista *ini, *fim;
} Fila;

/* cria fila vazia */
Fila *filaCriar (void);

/* verifica se a fila esta vazia */
int filaVazia (Fila *f);

/* acrescenta elemento ao final da fila */
void filaInserir (void *info, Fila *f);

/* "roda a fila", retira e retorna o primeiro elemento */
void *filaRetirar (Fila *f);

/* libera memoria usada pela fila */
void filaLiberar (Fila *f);

/* retorna quantidade de elementos na fila */
int filaTamanho (Fila *f);

#endif
