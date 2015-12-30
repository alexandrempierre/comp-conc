#include <stdlib.h>
#include "funcoes.h"
#include "arv.h"

#define PONTO_MEDIO(x0, x1)         ( 0.5 * (x0 + x1) )
#define RETANGULO_BASE(x0, x1)      ( x1 - x0 )
#define RETANGULO_ALTURA(x0, x1, f) ( f(PONTO_MEDIO(x0, x1)) )
#define RETANGULO_AREA(x0, x1, f)   ( RETANGULO_BASE(x0, x1) * RETANGULO_ALTURA(x0, x1, f) )

typedef struct estrIntegralDef {
  double areaComSinal, erro;
} IntegralDef;

double e;

double somarAreas (Arvore *areas) {
  double soma = 0;

  if (!arvVazia(areas)) {
    if (!arvVazia(areas->esq)) {
      soma += somarAreas(areas->esq);
      soma += somarAreas(areas->dir);
    }
    else {
      IntegralDef *integral;
      integral = (IntegralDef *) areas->info;
      soma += integral->areaComSinal;
    }
  }

  return soma;
}

Arvore *dividirAreas (double x0, double x1, FuncaoPtr f) {
  Arvore *areas;
  double area, subAreaA, subAreaB, m;
  IntegralDef *integral = (IntegralDef *)malloc(sizeof(IntegralDef));

  m = PONTO_MEDIO(x0, x1);
  area = RETANGULO_AREA(x0, x1, f);
  subAreaA = RETANGULO_AREA(x0, m, f);
  subAreaB = RETANGULO_AREA(m, x1, f);

  integral->areaComSinal = area;
  integral->erro = area - (subAreaA + subAreaB);

  areas = arvCriarNo((void *) integral, arvCriarVazia(), arvCriarVazia());

  if (fabs(integral->erro) > e) {
    areas->esq = dividirAreas(x0, m, f);
    areas->dir = dividirAreas(m, x1, f);
  }

  return areas;
}

double integrar(double x0, double x1, FuncaoPtr f) {
  Arvore *areas = dividirAreas(x0, x1, f);

  return somarAreas(areas);
}
