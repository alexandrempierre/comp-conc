#include <math.h>

#define FUNCOES_CONT 5

typedef double (*FuncaoPtr)(double);

/* Funcoes */
double fA (double x) { return 1.0 + x; }

double fB (double x) { return sqrt(1.0 - pow(x, 2.0)); }

double fC (double x) { return sqrt(1.0 - pow(x, 4.0)); }

double fD (double x) { return sin(pow(x, 2.0)); }

double fE (double x) { return cos(1.0/pow(M_E, x)) * (.005 * pow(x, 3.0) + 1.0); }

// double (* funcoes[FUNCOES_CONT])(double) = { &fA, &fB, &fC, &fD, &fE };
FuncaoPtr funcoes[FUNCOES_CONT] = { &fA, &fB, &fC, &fD, &fE };
