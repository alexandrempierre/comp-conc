#include <stdio.h>
#include <stdlib.h>

float **inicializar_matriz (int linhas, int colunas);

void preencher_matriz (float ***matriz, int linhas, int colunas, FILE * arq);

void produto_matrizes (float **M1, float **M2, int l_M1, int c_M2, int d, 
	float ***produto);

void imprimir_matriz (float **A, int m, int n);

void desalocar_matriz (float **matriz, int linhas);

int main (int argc, char *argv[]) {

	float **M1, **M2, **produto;
	int lin_M1, col_M1, lin_M2, col_M2, d; // dimensoes das matrizes
	int i, j, k; // iteradores
	float soma_produto;

	FILE *ptr_M1, *ptr_M2;
	const char *arq_M1 = argv[1];
	const char *arq_M2 = argv[2];

	printf("%s %s\n", arq_M1, arq_M2);

	ptr_M1 = fopen(arq_M1, "r");
	ptr_M2 = fopen(arq_M2, "r");

	fscanf(ptr_M1, "%d %d", &lin_M1, &col_M1);
	fscanf(ptr_M2, "%d %d", &lin_M2, &col_M2);

	if (col_M1 != lin_M2) {
		printf("--ERRO: O produto de matrizes so esta definido %s",
			"se quantidade de colunas da primeira for igual a de linhas da segunda \n"); 
		exit(-1);
	}

	d = col_M1;

	// ------------------------------------------------------------------------
	// -------------------------inicializacao das matrizes

	// inicializacao de M1
	M1 = inicializar_matriz(lin_M1, d);

	// inicializacao de M2
	M2 = inicializar_matriz(d, col_M2);

	// inicializacao da matriz produto
	produto = inicializar_matriz(lin_M1, col_M2);

	// ------------------------------------------------------------------------
	// -------------------------atribuicao de valores aos elementos
	
	// atribuicao de valores aos elementos de M1
	preencher_matriz(&M1, lin_M1, d, ptr_M1);

	// atribuicao de valores aos elementos de M2
	preencher_matriz(&M2, d, col_M2, ptr_M2);

	printf("M1: %d %d\n", lin_M1, col_M1);
	imprime(M1, lin_M1, col_M1);

	printf("\nM2: %d %d\n", lin_M2, col_M2);
	imprime(M2, lin_M2, col_M2);

	fclose(ptr_M1);
	fclose(ptr_M2);

	// ------------------------------------------------------------------------
	// -------------------------produto entre M1 e M2
	produto_matrizes(M1, M2, lin_M1, col_M2, d, &produto);

	printf("\nproduto: %d %d\n", lin_M1, col_M2);
	imprime(produto, lin_M1, col_M2);
	printf("\n");
	
	// ------------------------------------------------------------------------
	// -------------------------desalocar matrizes

	// desalocar M1
	desalocar_matriz(&M1, lin_M1);

	// desalocar M2
	desalocar_matriz(&M2, d);

	// ------------------------------------------------------------------------
	// -------------------------imprimir produto na saida padrao
	imprimir_matriz(produto, lin_M1, col_M2);

	return 0;
}

float **inicializar_matriz (int linhas, int colunas) {
	float **matriz;
	int i;

	matriz = malloc(linhas * sizeof(float *));
	if (matriz == NULL)
	{
		printf("--ERRO: malloc()\n"); exit(-1);
	}
	for (i = 0; i < linhas; ++i) {
		matriz[i] = (float *) malloc(colunas * sizeof(float));
		if (matriz[i] == NULL)
		{
			printf("--ERRO: malloc()\n"); exit(-1);
		}
	}

	return matriz;
}

void preencher_matriz (float ***matriz, int linhas, int colunas, FILE * arq) {
	int scan;

	int i, j;
	for (i = 0; i < linhas; ++i) {
		for (j = 0; j < colunas; ++j) {
			scan = fscanf(arq, "%f", &matriz[i][j]);
			if (scan == EOF || !scan) {
				printf("--ERRO: fscanf()"); exit(-1);
			}
		}
	}
}

void produto_matrizes (float **M1, float **M2, int l_M1, int c_M2, int d, 
	float ***produto) {
	
	int soma_produto;

	int i, j, k;
	for (i = 0; i < m; ++i) {
		for (j = 0; j < n; ++j) {
			soma_produto = 0;

			for (k = 0; k < d; ++k) {
				soma_produto += M1[i][k] * M2[k][j];
			}

			*produto[i][j] = soma_produto;
		}
	}
}

void imprimir_matriz (float **A, int m, int n) {
	int i, j;
	for (i = 0; i < m; ++i) {
		for (j = 0; j < n; ++j) {
			printf("%f ", A[i][j]);
		}
		printf("\n");
	}
}

void desalocar_matriz (float ***matriz, int linhas) {
	int i;
	for (i = 0; i < linhas; ++i)
		free(*matriz[i]);

	free(*matriz);
}
