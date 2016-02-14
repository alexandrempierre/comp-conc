#include <stdlib.h>
#include <stdio.h>
#include "elevadores.h"
#include "fila.h"
#include "andar.h"
#include "requisicao.h"
#include "var_globais.h"
#include <math.h>

int reqsPendentes (Elevador *elev) {
  int i, rP = 0;
  for (i = 0; i < C; ++i)
    if (elev->reqs[i] != NULL) rP++;

  return rP;
}

void embarcarPassageiros (Elevador *elev) {
  Fila *filaAndar = elev->andarAtual->fila;
  int i = 0;

  while (i < C && filaTamanho(filaAndar) > 0)
    elev->reqs[i++] = (Requisicao *) filaRetirar(filaAndar);
}

void desembarcarPassageiros (Elevador *elev) {
  Requisicao *reqs = elev->reqs;
  int i;

  for (i = 0; i < C; ++i)
    if (reqs[i]->destino == elev->andarAtual)
      reqs[i] = NULL;
}

void calcularCaminho (Elevador *elev) {
  int h, i;
  Fila *dests;

  if (reqsPendentes(elev) == 0) {
    /* Caminho para buscar passageiros */
  }
  else {
    dests = elev->distinos;

    for (i = 0; i < C; ++i)
      if (elev->reqs[i] != NULL && listaBuscar((void *) elev->reqs[i]->destino, dests->ini) == NULL)
          filaInserir((void *) elev->reqs[i]->destino, dests);
  }
}

void irProximoDestino (Elevador *elev) {
  elev->andarAtual = (Andar *) filaRetirar(elev->destinos);
}

void funcionar (Elevador *elev) {

}
