/* Autor: Mauricio Luiz Abreu Cardoso */
//------------------------------------------------------------------------------
// para compilar o programa de testes, substitua a minhaLu pela sua e execute
//
// gcc main.c ep2_test.c -lm -o ep2
//
// e depois, faÃ§a
//
// ./ep2
//
// para executar os testes
//------------------------------------------------------------------------------

#include "ep2_test.h"
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <stdio.h>

/* troca todos os valores da linha a apontada por a com 
** os valores da linha apontada por b */
void permute_linha(double* a, double * b, int n)
{
  int row_size = n * sizeof(double);


  double* aux = malloc(row_size);
  memcpy(aux, a, row_size);
  memcpy(a, b, row_size);
  memcpy(b, aux, row_size);
}


/* recebe a matriz quadrada x (alocada num vetor), a ordem n dessa matriz,
** e o vetor de permutacao p, e aloca em x a matriz L e U correspondente a
** x, e em p os índices que deverão ser permutados */
void minhaLu(double* x, int n, int* p)
{
  for(int i = 0; i < n; ++i) {
    p[i] = i;
  }

  for(int k = 0; k < n-1; k++, x += n + 1) {
  	int i_max = k;
  	double k_max = fabs(*x);
  	
  	double *c = x;
  	/* encontra a linha em que aij é o maior em módulo */
  	for(int i = k+1; i < n; i++) {
  		if(fabs(*(c += n) > k_max)) {
		  	i_max = i;
  			k_max = fabs(*c);
  		}
  	}

  	// se a linha k possui o maior aij em módulo, não é necessário permutar linhas
  	if(i_max > k) { 
  		double *linhaX = x-k;  //comeco da linha x
  		double *linhaImax = x-k + n*(i_max - k); // comeco da linha i_max
  		permute_linha(linhaX, linhaImax, n); 


  		int aux;
  		aux = p[k];
  		p[k] = p[i_max];
  		p[i_max] = aux;
  	}

  	/* comeco da proxima linha */  	
  	double* linha = x + n;
  	for (int i = k+1; i < n; ++i, linha += n)
  	{
  		double* linhaX = x;
  		double* linhaCalc = linha;
  		double quociente = *linhaCalc / *x;
  		*linha = quociente;

  		for(int j = k+1; j < n; j++) {
  			*(++linhaCalc) -= quociente * *(++linhaX);
  		}

  	}
  }


}


int main()
{
	/* teste da funcao minhaLu*/
/*	int n = 3;
	int* p = malloc (n * sizeof(int));
	double *v = malloc(n*n*sizeof(double));
	v[0] = 2;
	v[1] = 1;
	v[2] = 5;
	v[3] = 4;
	v[4] = 4;
	v[5] = -4;
	v[6] = 1;
	v[7] = 3;
	v[8] = 1;

	minhaLu(v, n, p);*/

	ep2_test(minhaLu);
  	return 0;
}