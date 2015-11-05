#include <stdio.h>
#include <stdlib.h>


int main (int argc, char *argv[]) {

	float **M1, **M2, **produto;
	int m, n; // dimensoes das matrizes
	int i, j, k; // iteradores
	float soma_produto;

	scanf("%d %d", &m, &n);

	// ------------------------------------------------------------------------
	// -------------------------inicializacao das matrizes

	// inicializacao de M1
	M1 = malloc(m * sizeof(float *));
	if (M1 == NULL)
	{
		printf("--ERRO: malloc()\n"); exit(-1);
	}

	for (i = 0; i < m; ++i)
	{
		M1[i] = (float *) malloc(n * sizeof(float));
		if (M1[i] == NULL)
		{
			printf("--ERRO: malloc()\n"); exit(-1);
		}
	}

	// inicializacao de M2
	M2 = malloc(m * sizeof(float *));
	if (M2 == NULL)
	{
		printf("--ERRO: malloc()\n"); exit(-1);
	}

	for (i = 0; i < m; ++i)
	{
		M2[i] = (float *) malloc(n * sizeof(float));
		if (M2[i] == NULL)
		{
			printf("--ERRO: malloc()\n"); exit(-1);
		}
	}

	// inicializacao da matriz produto
	produto = malloc(m * sizeof(float *));
	if (produto == NULL)
	{
		printf("--ERRO: malloc()\n"); exit(-1);
	}

	for (i = 0; i < m; ++i)
	{
		produto[i] = (float *) malloc(n * sizeof(float));
		if (produto[i] == NULL)
		{
			printf("--ERRO: malloc()\n"); exit(-1);
		}
	}


	// ------------------------------------------------------------------------
	// -------------------------atribuicao de valores aos elementos
	
	// atribuicao de valores aos elementos de M1
	for (i = 0; i < m; ++i)
		for (j = 0; j < n; ++j)
			scanf("%f", &M1[i][j]);

	// atribuicao de valores aos elementos de M2
	for (i = 0; i < m; ++i)
		for (j = 0; j < n; ++j)
			scanf("%f", &M2[i][j]);


	// ------------------------------------------------------------------------
	// -------------------------produto entre M1 e M2
	for (i = 0; i < m; ++i) {
		for (j = 0; j < n; ++j) {
			soma_produto = 0;

			for (k = 0; k < m; ++k) {
				soma_produto += M1[i][k] * M2[k][i];
			}

			produto[i][j] = soma_produto;
		}
	}
	
	// ------------------------------------------------------------------------
	// -------------------------desalocar matrizes

	// desalocar M1
	for (i = 0; i < m; ++i)
		free(M1[i]);

	free(M1);

	// desalocar M2
	for (i = 0; i < m; ++i) // d poderia ter sido usada no lugar de lin_M2
		free(M2[i]);

	free(M2);

	// ------------------------------------------------------------------------
	// -------------------------imprimir produto na saida padrao
	for (i = 0; i < m; ++i) {
		for (j = 0; j < n; ++j) {
			printf("%f ", produto[i][j]);
		}
		printf("\n");
	}

	return 0;
}
