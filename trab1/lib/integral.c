#include <stdlib.h>
#include <math.h>
#include "arv.h"
#include "integral.h"

#define PONTO_MEDIO(x0, x1)         ( 0.5 * (x0 + x1) )
#define ALTURA(x0, x1, f) ( f(PONTO_MEDIO(x0, x1)) )

#define AREA(x0, x1, h)             ( (x1 - x0) * h )

typedef struct estrIntegralDef {
  double areaComSinal, erro;
} IntegralDef;

typedef struct estrArea {
  double area;
  int def;
} Area;

/* A funcao abaixo soma os valores das folhas da arvore, ela so esta escrita
 * dessa forma porque a funcao que divide as areas nao cria o no da area que
 * nao vai ser utilizada, em lugar disso apenas calcula a area e verifica se o
 * erro exige que aquela area seja subdividida, em caso afirmativo os nos sao
 * criados
 */
double somarAreas (Arvore *areas) {
  double soma;
  TipoNo tipo = arvTipoNo(areas);

  switch (tipo) {
    case VAZIO: soma = 0; break;
    case FOLHA: soma = ((IntegralDef *) areas->info)->areaComSinal; break;
    case GALHO: soma = somarAreas(areas->esq) + somarAreas(areas->dir); break;
    default: break;
  }

  return soma;
}

Arvore *dividirAreas (Area areaRet, double x0, double x1) {
  Arvore *areas;
  double area, subAreaEsq, subAreaDir, m, h;
  IntegralDef *integral = (IntegralDef *) malloc(sizeof(IntegralDef));

  m = PONTO_MEDIO(x0, x1);
  h = funcao(m);
  area = areaRet.def ? areaRet.area : AREA(x0, x1, h);
  subAreaEsq = AREA(x0, m, ALTURA(x0, m, funcao));
  subAreaDir = AREA(m, x1, ALTURA(m, x1, funcao));

  integral->areaComSinal = area;
  integral->erro = fabs(area - (subAreaEsq + subAreaDir));

  areas = arvCriarNo((void *) integral, arvCriarVazia(), arvCriarVazia());

  if (integral->erro > erroMaximo) {
    areaRet.def = 1;
    areaRet.area = subAreaEsq;
    areas->esq = dividirAreas(areaRet, x0, m);

    areaRet.area = subAreaDir;
    areas->dir = dividirAreas(areaRet, m, x1);
  }

  return areas;
}

/* Funcao usada externamente para integrar */
double integrar(double x0, double x1, double e, FuncaoPtr f) {
  Area areaRet;
  areaRet.def = 0;

  erroMaximo = e;
  funcao = f;

  Arvore *areas = dividirAreas(areaRet, x0, x1);

  return somarAreas(areas);
}
