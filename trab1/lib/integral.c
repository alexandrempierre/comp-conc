#include <stdlib.h>
#include <math.h>
#include "arv.h"
#include "integral.h"

#define PONTO_MEDIO(x0, x1)         ( 0.5 * (x0 + x1) )
#define RETANGULO_BASE(x0, x1)      ( x1 - x0 )
#define RETANGULO_ALTURA(x0, x1, f) ( f(PONTO_MEDIO(x0, x1)) )
#define RETANGULO_AREA(x0, x1, f)   ( RETANGULO_BASE(x0, x1) * RETANGULO_ALTURA(x0, x1, f) )

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

Arvore *dividirAreas (Area areaRet, double x0, double x1, double erroMaximo, FuncaoPtr f) {
  Arvore *areas;
  double area, subAreaEsq, subAreaDir, m;
  IntegralDef *integral = (IntegralDef *) malloc(sizeof(IntegralDef));

  m = PONTO_MEDIO(x0, x1);
  area = areaRet.def ? areaRet.area : RETANGULO_AREA(x0, x1, f);
  subAreaEsq = RETANGULO_AREA(x0, m, f);
  subAreaDir = RETANGULO_AREA(m, x1, f);

  integral->areaComSinal = area;
  integral->erro = area - (subAreaEsq + subAreaDir);

  areas = arvCriarNo((void *) integral, arvCriarVazia(), arvCriarVazia());

  if (fabs(integral->erro) > erroMaximo) {
    areaRet.def = 1;
    areaRet.area = subAreaEsq;
    areas->esq = dividirAreas(areaRet, x0, m, erroMaximo, f);
    
    areaRet.area = subAreaDir;
    areas->dir = dividirAreas(areaRet, m, x1, erroMaximo, f);
  }

  return areas;
}

/* Funcao usada externamente para integrar */
double integrar(double x0, double x1, double erroMaximo, FuncaoPtr f) {
  Area areaRet;
  areaRet.def = 0;

  Arvore *areas = dividirAreas(areaRet, x0, x1, erroMaximo, f);

  return somarAreas(areas);
}
