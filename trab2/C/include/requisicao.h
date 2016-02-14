#ifndef H_REQUISICAO
#define H_REQUISICAO

#include "andar.h"

typedef struct estrRequisicao {
  int id;
  Andar *destino;
} Requisicao;

#endif
