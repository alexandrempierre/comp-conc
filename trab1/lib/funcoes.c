#include <math.h>
#include "funcoes.h"

#define QUADRADO(x) pow(x,2)
#define CUBO(x)     pow(x,3)
#define QUARTA(x)   pow(x,4)

/* Funcoes */
double fA (double x) { return 1.0 + x; }

double fB (double x) { return sqrt(1.0 - QUADRADO(x)); }

double fC (double x) { return sqrt(1.0 - QUARTA(x)); }

double fD (double x) { return sin(QUADRADO(x)); }

double fE (double x) { return cos(pow(M_E, -x)) * (.005 * CUBO(x) + 1.0); }

// double (* funcoes[FUNCOES_CONT])(double) = { &fA, &fB, &fC, &fD, &fE };
FuncaoPtr funcoes[FUNCOES_CONT] = { &fA, &fB, &fC, &fD, &fE };
