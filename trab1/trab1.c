#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// #include "timer.h"
// #include <pthread.h>

double fA (double x) { return 1.0 + x; }

double fB (double x) { return sqrt(1.0 - pow(x, 2.0)); }

double fC (double x) { return sqrt(1.0 - pow(x, 4.0)); }

double fD (double x) { return sin(pow(x, 2.0)); }

double fE (double x) { return cos(pow(M_E, -x)) * (.005 * pow(x, 3.0) + 1.0); }

double area (double x1, double x2, double (*f)(double) ) {
  double base, altura;

  base = x2 > x1 ? x2 - x1 : x1 - x2; // define o tamanho da base suubtraindo o menor parametro do maior
  altura = (f(x1) + f(x2)) / 2; // define a altura como a media entre as alturas

  return base * altura;
}

int main(int argc, char const *argv[]) {
  double result = area(0, -1.0, &fA);

  printf("%f\n", result);
  return 0;
}
