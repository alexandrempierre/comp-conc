#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// #include "timer.h"
// #include <pthread.h>

double fA (double x) {
  return 1.0 + x;
}
double fB (double x) {
  return sqrt(1.0 - pow(x, 2.0));
}

double fC (double x) {
  return sqrt(1.0 - pow(x, 4.0));
}

double fD (double x) {
  return sin(pow(x, 2.0));
}

double fE (double x) {
  return cos(pow(M_E, -x)) * (.005 * pow(x, 3.0) + 1.0);
}
