#include <stdio.h>  // Entrada e saida padrao
#include <stdlib.h> // Biblioteca padrao com funcoes como exit()
#include <math.h>   // Para usar a funcao fabs()
// #include <pthread.h>
// #include "timer.h"
#include "funcoes.h"
#include "integral.h"

int main (int argc, char const *argv[]) {
  double a, b, e, area;
  int argumentosOk = 3;

  /* Teste dos argumentos de entrada */

  /* Teste do numero de argumentos de entrada */
  if (argc != 4) {
    printf("Use: %s <inicio do intervalo> <fim do intervalo> <erro maximo>\n", argv[0]);
    exit(-1);
  }

  /* Teste do formato dos argumentos de entrada */
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

  /* Integral */
  e = fabs(e); // Transforma o erro num numero nao-negativo
  area = integrar(a, b, e, funcoes[0]);

  printf("Integral definida em [%f, %f]: %f\n", a, b, area);

  return 0;
}
