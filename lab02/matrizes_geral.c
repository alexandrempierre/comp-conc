#include <stdio.h>
#include <stdlib.h>


int main (int argc, char *argv[]) {

	float **M1, **M2, **produto;
	int lin_M1, col_M1, lin_M2, col_M2, d; // dimensoes das matrizes
	int i, j, k; // iteradores
	float soma_produto;

	scanf("%d %d %d %d", &lin_M1, &col_M1, &lin_M2, &col_M2);

	if (col_M1 != lin_M2) {
		printf("--ERRO: O produto de matrizes so esta definido %s",
			"se quantidade de colunas da primeira for igual a de linhas da segunda \n"); 
		exit(-1);
	}

	d = col_M1;

	printf("%d %d\n", lin_M1, col_M2); exit(-1);

	// ------------------------------------------------------------------------
	// -------------------------inicializacao das matrizes

	// inicializacao de M1
	M1 = malloc(lin_M1 * sizeof(float *));
	if (M1 == NULL)
	{
		printf("--ERRO: malloc()\n"); exit(-1);
	}

	for (i = 0; i < lin_M1; ++i)
	{
		M1[i] = (float *) malloc(d * sizeof(float));
		if (M1[i] == NULL)
		{
			printf("--ERRO: malloc()\n"); exit(-1);
		}
	}

	// inicializacao de M2
	M2 = malloc(d * sizeof(float *));
	if (M2 == NULL)
	{
		printf("--ERRO: malloc()\n"); exit(-1);
	}

	for (i = 0; i < d; ++i)
	{
		M2[i] = (float *) malloc(col_M2 * sizeof(float));
		if (M2[i] == NULL)
		{
			printf("--ERRO: malloc()\n"); exit(-1);
		}
	}

	// inicializacao da matriz produto
	produto = malloc(lin_M1 * sizeof(float *));
	if (produto == NULL)
	{
		printf("--ERRO: malloc()\n"); exit(-1);
	}

	for (i = 0; i < lin_M1; ++i)
	{
		produto[i] = (float *) malloc(col_M2 * sizeof(float));
		if (produto[i] == NULL)
		{
			printf("--ERRO: malloc()\n"); exit(-1);
		}
	}


	// ------------------------------------------------------------------------
	// -------------------------atribuicao de valores aos elementos
	
	// atribuicao de valores aos elementos de M1
	for (i = 0; i < lin_M1; ++i)
		for (j = 0; j < d; ++j)
			scanf("%f", &M1[i][j]);

	// atribuicao de valores aos elementos de M2
	for (i = 0; i < d; ++i)
		for (j = 0; j < col_M2; ++j)
			scanf("%f", &M2[i][j]);


	// ------------------------------------------------------------------------
	// -------------------------produto entre M1 e M2
	for (i = 0; i < lin_M1; ++i) {
		for (j = 0; j < col_M2; ++j) {
			soma_produto = 0;

			for (k = 0; k < d; ++k) {
				soma_produto += M1[i][k] * M2[k][i];
			}

			produto[i][j] = soma_produto;
		}
	}
	
	// ------------------------------------------------------------------------
	// -------------------------desalocar matrizes

	// desalocar M1
	for (i = 0; i < lin_M1; ++i)
		free(M1[i]);

	free(M1);

	// desalocar M2
	for (i = 0; i < lin_M2; ++i) // d poderia ter sido usada no lugar de lin_M2
		free(M2[i]);

	free(M2);

	// ------------------------------------------------------------------------
	// -------------------------imprimir produto na saida padrao
	for (i = 0; i < lin_M1; ++i) {
		for (j = 0; j < col_M2; ++j) {
			printf("%f ", produto[i][j]);
		}
		printf("\n");
	}

	return 0;
}
