#include <stdio.h>
#include <stdlib.h>
// #include <pthread.h>
// #include <semaphore.h>
#include "elevadores.h"
#include "requisicao.h"
#include "andar.h"
#include "fila.h"
#include "var_globais.h"

/* Variaveis globais:
 *
 * Elevador *elevadores;
 * Andar *andares;
 * int N, M, C;
 */

/* N: numero de andares         (5 <= N <= 100)
 * M: numero de elevadores      (5 <= M <= 20)
 * C: capacidade dos elevadores (5 <= C <= 20)
 */

int main(int argc, char const *argv[]) {

  int i, j;
  Requisicao *requisicao;

  FILE *entrada, *logMain;

  // nome do arquivo com entradas passado por linha de comando
  entrada = fopen(argv[1], "r");

  // N, M e C lidos do arquivo e elevadores inicializados
  fscanf(entrada, "%d %d %d", &N, &M, &C);
  // *elevadores = (Elevador *) malloc(M * sizeof(Elevador));
  *elevadores = VETOR(Elevador, M);

  // lidas do arquivo requisicoes para o elevador
  int destino, id = 0, qtdeReqs;
  *andares =  VETOR(Andar, N);

  for (i = 0; i < N; ++i) {

    fscanf(entrada, "%d", &qtdeReqs);

    andares[i] = PONTEIRO(Andar);
    andares[i]->numAndar = i;

    for (j = 0; j < qtdeReqs; ++j) {

      fscanf(entrada, "%d", &destino);

      requisicao = PONTEIRO(Requisicao);
      requisicao->id = id++;
      requisicao->destino = andares[destino];

      filaInserir(andares[i]->fila, (void *) requisicao);
    }
  }

  // lido do arquivo o andar em que cada elevador esta
  int andar;
  for (i = 0; i < M; ++i) {

    fscanf(entrada, "%d", &andar);

    elevadores[i] = PONTEIRO(Elevador);
    elevadores[i]->andarAtual = andares[andar];
    elevadores[i]->destinos = filaCriar();
  }

  /* Criar threads que vao lidar com elevadores */

  /* Aguardar fim das threads que vao lidar com elevadores */

  // Registro das atividades da thread principal num arquivo
  logMain = fopen("log/main.txt", "w");
  fprintf(logMain, "N: %d\tM: %d\tC: %d\n", N, M, C);

  for(i = 0; i < M; ++i)
    fprintf(logMain, "Elevador %d - Andar atual: %d\n", i, elevadores[i]->andarAtual->numAndar);

  // fechamento dos arquivos abertos
  fclose(entrada);
  fclose(logMain);



  return 0;
}
