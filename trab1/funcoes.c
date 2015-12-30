#include <math.h>

#define FUNCOES_CONT 5
#define QUADRADO(x) (x*x)
#define CUBO(x)     (x*x*x)
#define QUARTA(x)   (QUADRADO(x)*QUADRADO(x))

typedef double (*FuncaoPtr)(double);

/* Funcoes */
double fA (double x) { return 1.0 + x; }

double fB (double x) { return sqrt(1.0 - QUADRADO(x)); }

double fC (double x) { return sqrt(1.0 - QUARTA(x)); }

double fD (double x) { return sin(QUADRADO(x)); }

double fE (double x) { return cos(1.0 / pow(M_E, x)) * (.005 * CUBO(x) + 1.0); }

// double (* funcoes[FUNCOES_CONT])(double) = { &fA, &fB, &fC, &fD, &fE };
FuncaoPtr funcoes[FUNCOES_CONT] = { &fA, &fB, &fC, &fD, &fE };
