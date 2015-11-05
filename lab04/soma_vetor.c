#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> //para usar a funcao "sysconf"

/* Variaveis globais */
int nthreads, tam;
float *vetor;

/* Prototipos das funcoes */

float soma_seq ();

float soma_seq_intercalada ();

float soma_seq_bloco ();

void * soma_bloco (void * tid);

void * soma_intercalada (void * tid);

/* Funcao principal */

int main (int argc, char const *argv[]) {
	FILE *ptr_arquivo; //ponteiro para arquivo com tamanho e elementos do vetor
	int i; // iterador
	pthread_t *tid_sistema; //vetor de identificadores das threads no sistema
	int *tid; //identificadores das threads no programa
	int numCPU; //numero de processadores

	float soma_conc = 0, soma_sequ = 0, soma_sequ_corr = 0; // soma dos elementos do vetor
	float *retorno;

	/* Teste da chamada do programa */
	if (argc < 3) {
		printf("%s <nome do arquivo> <numero de threads>\n", argv[0]); exit(-1);
	}

	retorno = (float *) malloc(sizeof(float));
	if (retorno == NULL) {
		printf("--ERRO: malloc()\n"); exit(-1);
	}

	nthreads = atoi(argv[2]);

	//descobre o numero de proccessadores que a maquina possui
	numCPU = sysconf(_SC_NPROCESSORS_ONLN);
	printf("Numero de processadores: %d\n", numCPU);

	if (nthreads > numCPU)
		nthreads = numCPU;
	else if (nthreads < 1)
		nthreads = 1;

	/*Abrir arquivo*/
	ptr_arquivo = fopen(argv[1], "r");
	if (ptr_arquivo == (FILE *) NULL) {
		printf("--ERRO: fopen()\n"); exit(-1);
	}

	/*Obter tamanho do vetor*/
	if (!fscanf(ptr_arquivo, "%d", &tam)) {
		printf("--ERRO: fscanf()\n"); exit(-1);
	}

	/*Inicializar vetor*/
	vetor = malloc(tam * sizeof(float));
	if (vetor == (float *) NULL) {
		printf("--ERRO: malloc()\n"); exit(-1);
	}

	/*Preencher elementos do vetor*/
	for (i = 0; i < tam; ++i) {
		if (!fscanf(ptr_arquivo, "%f", &vetor[i])) {
			printf("--ERRO: fscanf()\n"); exit(-1);
		}
	}

	fclose(ptr_arquivo);

	/* Soma sequencial */
	soma_sequ = soma_seq();
	printf("Soma sequencial: %.8f\n\n", soma_sequ);

	/* Soma concorrente */

	/* Inicializacao do vetor com os identificadores das threads no sistema */
	tid_sistema = (pthread_t *) malloc(nthreads * sizeof(pthread_t));
	if (tid_sistema == (pthread_t *) NULL) {
		printf("--ERRO: malloc()\n"); exit(-1);
	}

	/* Criacao das threads */
	for (i = 0; i < nthreads; ++i) {
		tid = malloc(sizeof(int));
		if (tid == NULL) {
			printf("--ERRO: malloc()\n"); exit(-1);
		}

		*tid = i;
		if ( pthread_create(&tid_sistema[i], NULL, soma_intercalada, (void *) tid) ) {
		// if ( pthread_create(&tid_sistema[i], NULL, soma_bloco, (void *) tid) ) {
			printf("--ERRO: pthread_create()\n"); exit(-1);
		}
	}

	/* Espera todas as threads terminarem */
	for (i = 0; i < nthreads; ++i) {
		if ( pthread_join(tid_sistema[i], (void *) &retorno) ) {
			printf("--ERRO: pthread_join()\n"); exit(-1);
		}

		soma_conc += *retorno;
	}
	printf("Soma concorrente %s: %.8f\n", "intercalada", soma_conc);

	/* Soma sequencial correspondente a concorrente (mesmo resultado) */
	soma_sequ_corr = soma_seq_intercalada();
	// soma_sequ_corr = soma_seq_bloco();
	printf("Soma sequencial correspondente: %.8f\n", soma_sequ_corr);

	free(vetor);
	free(tid_sistema);

	return 0;
}

/* Conteudo das Funcoes */

/* Funcoes sequenciais */

float soma_seq (float * vetor, int tam) {
	int i;
	float soma = 0.0;

	for (i = 0; i < tam; ++i) {
		soma += vetor[i];
	}

	return soma;
}

float soma_seq_intercalada () {
	int i, j;
	float *somas, total = 0;

	somas = malloc(nthreads * sizeof(float));
	if (somas == (float *) NULL) {
		printf("--ERRO: malloc()\n"); exit(-1);
	}

	for (i = 0; i < nthreads; ++i) {
		somas[i] = 0;

		for (j = i; j < tam; j += nthreads) {
			somas[i] += vetor[j];
		}

		total += somas[i];
	}

	return total;
}

float soma_seq_bloco () {
	int id, i, inicio, fim, resto;
	float soma = 0;

	resto = tam % nthreads;
	for (id = 0; id < nthreads; ++id) {
		inicio = id * tam/nthreads;
		fim = (id + 1) * tam/nthreads;
		for (i = inicio; i < fim; ++i) {
			soma += vetor[i];
		}

		fim = id + nthreads * tam/nthreads;
		if (resto && fim < tam) {
			soma += vetor[fim];
		}
	}

	return soma;
}

/* Funcoes concorrentes */

void * soma_bloco (void * tid) {
	int id = * (int *) tid;
	free(tid);

	int i, inicio, fim, resto;
	float soma = 0;
	float *ret;
	
	ret = malloc(sizeof(float));
	if (ret == (float *) NULL) {
		printf("--ERRO: malloc()\n"); exit(-1);
	}

	inicio = id * tam/nthreads;
	fim = (id + 1) * tam/nthreads;
	for (i = inicio; i < fim; ++i) {
		soma += vetor[i];
	}

	resto = tam % nthreads;
	fim = id + nthreads * tam/nthreads;
	if (resto && fim < tam) {
		soma += vetor[fim];
	}

	*ret = soma;
	pthread_exit( (void *) ret );
}

void * soma_intercalada (void * tid) {
	int id = * (int *) tid;
	free(tid);

	int i;
	float soma = 0;
	float *ret;
	
	ret = malloc(sizeof(float));
	if (ret == (float *) NULL) {
		printf("--ERRO: malloc()\n"); exit(-1);
	}

	for (i = 0; i < tam; i += nthreads) {
		soma += vetor[i];
	}

	*ret = soma;
	pthread_exit( (void *) ret );
}
