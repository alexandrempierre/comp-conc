#include <stdio.h>
#include <stdlib.h>

int **inicializar_matriz (int linhas, int colunas);

void imprimir_matriz (int **matriz, int linhas, int colunas);

int main (int argc, char *argv[]) {
	int **A, **B, **produto;
	int m, n, p; // dimensoes das matrizes
	int i, j, k; // iteradores
	int soma_produto;

	m = atoi(argv[1]);
	p = atoi(argv[2]);
	n = atoi(argv[3]);

	A = inicializar_matriz(m, p);
	B = inicializar_matriz(p, n);
	produto = inicializar_matriz(m, n);

	for (i = 0; i < m; ++i)
		for (j = 0; j < p; ++j)
			scanf("%d", &A[i][j]);

	for (i = 0; i < p; ++i)
		for (j = 0; j < n; ++j)
			scanf("%d", &B[i][j]);

	printf("A:\n");
	imprimir_matriz(A, m, p);
	printf("B:\n");
	imprimir_matriz(B, p, n);

	for (i = 0; i < m; ++i)
	{
		for (j = 0; j < n; ++j)
		{
			soma_produto = 0;
			for (k = 0; k < p; ++k)
			{
				soma_produto += A[i][k]*B[k][j];
			}
			produto[i][j] = soma_produto;
		}
	}

	imprimir_matriz(produto, m, n);

	return 0;
}

int **inicializar_matriz (int linhas, int colunas) {
	int i, **matriz;

	matriz = malloc(linhas * sizeof(int *));

	if (matriz == NULL)
	{
		printf("--ERRO: malloc()\n"); exit(-1);
	}

	for (i = 0; i < linhas; ++i)
	{
		matriz[i] = malloc(colunas * sizeof(int));

		if (matriz[i] == NULL)
		{
			printf("--ERRO: malloc()\n"); exit(-1);
		}
	}

	return matriz;
}

void imprimir_matriz (int **matriz, int linhas, int colunas) {
	int i, j;
	for (i = 0; i < linhas; ++i) {
		for (j = 0; j < colunas; ++j) {
			printf("%d ", matriz[i][j]);
		}
		printf("\n");
	}
}
