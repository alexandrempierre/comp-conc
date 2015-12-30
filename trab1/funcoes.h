#ifndef _H_FUNCOES
#define _H_FUNCOES

#include <math.h>

#define FUNCOES_CONT 5

typedef double (*FuncaoPtr)(double);

double fA (double x);
double fB (double x);
double fC (double x);
double fD (double x);
double fE (double x);

FuncaoPtr funcoes[FUNCOES_CONT];

#endif
