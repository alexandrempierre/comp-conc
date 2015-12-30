#include <stdio.h>
#include <stdlib.h>
#include "integral.h"
#include "funcoes.h"
#include <math.h>

double f (double x) { return cos(x); }

int main(int argc, char const *argv[]) {
  double a, b, area;
  int argumentosOk = 3;

  /* Teste dos argumentos de entrada */

  /* Teste do numero de argumentos de entrada */
  if (argc != 4) {
    printf("Use: %s <inicio do intervalo> <fim do intervalo> <erro maximo>\n", argv[0]);
    exit(-1);
  }

  /* Teste do formato das entradas */
  if (sscanf(argv[1], "%lf", &a) != 1) {
    printf("--ERRO: primeiro argumento (inicio do intervalo) esta fora do padrao\n");
    printf("Esperado um valor do tipo double\n\n");
    argumentosOk--;
  }

  if (sscanf(argv[2], "%lf", &b) != 1) {
    printf("--ERRO: segundo argumento (fim do intervalo) esta fora do padrao\n");
    printf("Esperado um valor do tipo double\n\n");
    argumentosOk--;
  }

  if (sscanf(argv[3], "%lf", &e) != 1) {
    printf("--ERRO: terceiro argumento (erro maximo) esta fora do padrao\n");
    printf("Esperado um valor do tipo double\n\n");
    argumentosOk--;
  }

  if (argumentosOk < 3) { exit(-1); }

  e = fabs(e);

  area = integrar(a, b, f);

  printf("Area: %lf\n", area);

  return 0;
}
