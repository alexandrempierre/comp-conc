#ifndef _H_INTEGRAL
#define _H_INTEGRAL

#include "funcoes.h"

double erroMaximo;
FuncaoPtr funcao;

double integrar (double x0, double x1, double erroMaximo, FuncaoPtr f);

#endif
