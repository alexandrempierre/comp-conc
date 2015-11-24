#include <stdio.h>
#include <stdlib.h>
#include <math.h> //necessario para usar sqrt()
#include "timer.h"
#include <phtread.h>

/* Enunciado
 *
 * Dada uma sequencia de numeros inteiros positivos 1 a N (N muito grande),
 * identificar todos os numeros primos e retornar a quantidade total de
 * numeros primos encontrados.
 */

/* Variaveis globais */
long long int N; //limite para teste de primalidade
pthread_mutex_t bastao; //variavel de lock para exclusao mutua
int nThreads;

/* Funcoes */
int ehPrimo (long long int n) {
  int i;

  if (n<=1) return 0;
  if (n==2) return 1;
  if (n%2==0) return 0;

  for (i=3; i<sqrt(n)+1; i+=2)
    if(n%i==0) return 0;

  return 1;
}

int contaPrimosSeq () {
  int qPrimos = 0;

  // Testa a primalidade dos numeros de N ate 2
  for ( ; N > 1; N--) {
    if (ehPrimo(N)) { qPrimos++; }
  }

  return qPrimos;
}

void * contaPrimosConc (void * tid) {
  int id = * (int *) tid;
  int qPrimos, *retorno;
  long long int i;

  qPrimos = 0;

  if ((retorno = malloc(sizeof(int))) == NULL)
    printf("--ERRO: malloc()\n"); exit(-1);

  while (N > 1) {
    // entrada na secao critica
    pthread_mutex_lock(&bastao);
    // secao critica
    N--; // decrementa N
    // saida da secao critica
    pthread_mutex_unlock(&bastao);

    if (ehPrimo(N)) { qPrimos++; }
  }

  free(tid);

  *retorno = qPrimos;
  pthread_exit((void *) retorno);
}

/* Funcao principal */
int main(int argc, char const *argv[]) {
  double ini, fi, inicio, final, procSeq, procConc, speedup;
  int *id, *retorno, i, qPrimosSeq = 0, qPrimosConc = 0;

  pthread_t *tid_sistema;

  GET_TIME(ini); //Tomada de tempo da inicializacao do programa (necessariamente sequencial)

  /* Teste da entrada */
  //Teste da quantidade de argumentos de linha de comando
  if (argc < 3) { printf("Use: %s <N> <numero de threads>\n", argv[0]); exit(-1); }

  N = atoll(argv[1]);
  nThreads = atoi(argv[2]);

  if (nThreads < 1) { printf("--ERRO: numero de threads menor que 1\n"); exit(-1); }

  printf("Quantidade de numeros de 1 a %lld (inclusive): ", N);

  GET_TIME(fi); //Tomada de tempo da inicializacao do programa (necessariamente sequencial)
  inicio = fi - ini; // tempo de inciializacao do programa

  /*-----------------------------------------------------------------------------------------*/
  GET_TIME(ini); //Tomada de tempo do processamento sequencial

  /* Chamada sequencial da contagem de primos */
  qPrimos = contaPrimosSeq();

  GET_TIME(fi); //Tomada de tempo do processamento sequencial
  procSeq = fi - ini; // tempo do processamento sequencial
  /*-----------------------------------------------------------------------------------------*/

  GET_TIME(ini);

  pthread_mutex_init(&bastao, NULL); // inicializa o lock de exclusao mutua

  // cria as threads
  for (i = 0; i < nThreads; ++i) {
    if ((id = malloc(sizeof(int))) == NULL) {
      printf("--ERRO: malloc()\n"); exit(-1);
    }
    *id = i;

    if (pthread_create(&tid_sistema, NULL, contaPrimosConc, (void *)id)) {
      printf("--ERRO: pthread_create()\n"); exit(-1);
    }
  }

  //aguarda o fim das threads
  for (i = 0; i < nThreads; ++i) {

  }

  GET_TIME(fi);
  procConc = fi - ini;
  /*-----------------------------------------------------------------------------------------*/

  GET_TIME(ini); //Tomada de tempo da finalizacao do programa (necessariamente sequencial)

  printf("%d\n", qPrimos);

  GET_TIME(fi); //Tomada de tempo da finalizacao do programa (necessariamente sequencial)
  final = fi - ini; // tempo da finalizacao do programa

  procSeq += (inicio + final);
  procConc += (inicio + final);
  speedup = procSeq/procConc;

  printf("Tempo Sequencial: %f\n", procSeq);
  printf("Tempo Concorrente: %f\n", procConc);
  printf("Speedup: %f\n", speedup);

  return 0;
}
