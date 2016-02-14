#ifndef H_ELEVADORES
#define H_ELEVADORES

#include "requisicao.h"
#include "fila.h"

/* C: capacidade dos elevadores (5 <= C <= 20) */
int C;

typedef struct estrElevador {
  Andar *andarAtual;
  // Vetor de ponteiros para requisicoes
  Requisicao** reqs;
  Fila *destinos;
} Elevador;

Elevador **elevadores;

#endif
