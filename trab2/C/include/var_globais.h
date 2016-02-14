#ifndef H_VAR_GLOBAIS
#define H_VAR_GLOBAIS

#include <stdlib.h>

#define PONTEIRO(tipo)       (tipo *)malloc(sizeof(tipo))
#define VETOR(tipo, tamanho) (tipo *)malloc(tamanho * sizeof(tipo))

/* N: numero de andares     (5 <= N <= 100)
 * M: numero de elevadores  (5 <= M <= 20) */
int N, M;



#endif
