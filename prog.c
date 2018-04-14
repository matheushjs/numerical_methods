#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DOUBLE double

// Retorna a norma infinita de um vetor
DOUBLE infinite_norm(DOUBLE *vec, int n){
	int i;
	DOUBLE max = fabs(vec[0]);
	for(i = 1; i < n; i++){
		DOUBLE elem = fabs(vec[i]);
		if(elem > max) max = elem;
	}
	return max;
}

// Retorna a norma infinita de vec1 - vec2
DOUBLE infinite_norm_diff(DOUBLE *vec1, DOUBLE *vec2, int n){
	int i;
	DOUBLE max = fabs(vec1[0] - vec2[0]);
	for(i = 1; i < n; i++){
		DOUBLE elem = fabs(vec1[i] - vec2[i]);
		if(elem > max) max = elem;
	}
	return max;
}

/* Resolve o sistema A.x = b utilizando o método de Gauss-Seidel.
 * A aproximação inicial deve estar em 'x0'. Se 'x0' for NULL, assumimos
 *   que x0 deve ser o vetor nulo.
 * O vetor solução é retornado.
 */
DOUBLE *gauss_seidel(DOUBLE **A, DOUBLE *b, int n, DOUBLE eps, int itmax, DOUBLE *x0){
	int i, j, it;

	// Alocar vetor de soluções a cada iteração
	DOUBLE *xk = (DOUBLE *) malloc(sizeof(DOUBLE) * n);

	// Alocar vetor de soluções da iteração anterior
	DOUBLE xlast[n];

	if(x0 == NULL) // Inicializar xk
		for(i = 0; i < n; i++) xk[i] = 0;
	else           // Copiar de x0 para xk
		for(i = 0; i < n; i++) xk[i] = x0[i];
	
	// Iterações do método
	for(it = 0; it < itmax; it++){
		// Calculamos x_k+1 para cada elemento do vetor de soluções
		for(i = 0; i < n; i++){
			// Variável de acumulação
			DOUBLE acc = b[i];

			// Iteramos sobre as soluções já calculadas
			for(j = 0; j < i; j++){
				acc -= xk[j] * A[i][j];
			}
			
			// Iteramos sobre as soluções ainda não calculadas
			for(j = i+1; j < n; j++){
				acc -= xk[j] * A[i][j];
			}

			// Divisão final
			acc /= A[i][i];

			// Colocamos a solução atual como solução anterior
			xlast[i] = xk[i];

			// Finalmente, x_k <- x_(k+1)
			xk[i] = acc;
		}
		
		// Verificamos a norma infinita
		DOUBLE norm = infinite_norm_diff(xk, xlast, n);
		if(norm <= eps) break;;
	}

	return xk;
}

void teste_letraB(int n){
	int i, j;

	printf("\n\nRealizando teste letra b) com n = %d\n", n);

	// Cria matrizes A e b
	DOUBLE *A[n];
	DOUBLE AA[n][n];
	DOUBLE b[n];
	for(i = 0; i < n; i++) A[i] = (DOUBLE *) AA[i];

	// Preenche matriz A e b, a_ii = i*i, todo o resto é 0
	for(i = 0; i < n; i++){
		DOUBLE bsum = 0;
		for(j = 0; j < n; j++){
			if(i == j)   A[i][j] =  4;
			else if(i+1 == j) A[i][j] = -1;
			else if(i == j+1) A[i][j] = -1;
			else if(i+3 == j) A[i][j] = -1;
			else if(i == j+3) A[i][j] = -1;
			else A[i][j] = 0;
			bsum += A[i][j];
		}
		b[i] = bsum;
	}
	
	DOUBLE *ret = gauss_seidel(A, b, n, 1E-10, 500000, NULL);

	printf("Resultado: ( ");
	for(i = 0; i < n; i++) printf("%lf ", ret[i]);
	printf(")\n");

	free(ret);
}

void teste_letraC(int n){
	int i, j;

	printf("\n\nRealizando teste letra c) com n = %d\n", n);
	
	// Cria matrizes A e b
	DOUBLE *A[n];
	DOUBLE AA[n][n];
	DOUBLE b[n];
	for(i = 0; i < n; i++) A[i] = (DOUBLE *) AA[i];
	
	// Preenche A da maneira especificada
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			if(i == j)   A[i][j] =  4;
			else if(i+1 == j) A[i][j] = -1;
			else if(i == j+1) A[i][j] = -1;
			else if(i+3 == j) A[i][j] = -1;
			else if(i == j+3) A[i][j] = -1;
			else A[i][j] = 0;
			// printf("%lf ", A[i][j]);
		}
		// printf("\n");
	}

	// Preenche b
	for(i = 0; i < n; i++)
		b[i] = 1.0 / (i+1);

	// Calcula a solução. 'NULL' faz a aproximação inicial ser o vetor nulo.
	DOUBLE *ret = gauss_seidel(A, b, n, 1E-10, 500000, NULL);

	printf("Resultado: ( ");
	for(i = 0; i < n; i++) printf("%lf ", ret[i]);
	printf(")\n");

	free(ret);
}


int main(int argc, char *argv[]){
	teste_letraB(50);
	teste_letraB(100);
	teste_letraC(50);
	return 0;
}
