#ifndef _H_INTEGRAL
#define _H_INTEGRAL

#include "funcoes.h"
#include "arv.h"

Arvore *dividirAreas (double x0, double x1, double erroMaximo, FuncaoPtr f);
double somarAreas (Arvore *areas);
double integrar (double x0, double x1, double erroMaximo, FuncaoPtr f);

#endif
