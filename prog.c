#include <stdio.h>
#include <stdlib.h>

#define DOUBLE double

/* Resolve o sistema A.x = b utilizando o método de Gauss-Seidel.
 * A aproximação inicial deve estar em 'x0'. Se 'x0' for NULL, assumimos
 *   que x0 deve ser o vetor nulo.
 * O vetor solução é retornado.
 */
DOUBLE *gauss_seidel(DOUBLE A[][2], DOUBLE *b, int n, DOUBLE eps, int itmax, DOUBLE *x0){
	int i, j, it;

	// Alocar vetor de soluções a cada iteração
	DOUBLE *xk = (DOUBLE *) malloc(sizeof(DOUBLE) * n);

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

			// Finalmente, x_k <- x_(k+1)
			xk[i] = acc;
		}

		printf("x%d: (%lf, %lf)\n", it, xk[0], xk[1]);
	}

	return xk;
}

int main(int argc, char *argv[]){
	double A[][2] = {{2, 1}, {3, 4}};
	double b[] = {1, -1};
	int n = 2;
	int itmax = 50;
	double eps = 1E-10;

	double *res = gauss_seidel(A, b, n, eps, itmax, NULL);

	printf("Expected: (%lf, %lf)\n", 1.0, -1.0);
	printf("We got:   (%lf, %lf)\n", res[0], res[1]);

	free(res);

	return 0;
}
