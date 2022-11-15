#ifdef _OPENMP
	#include <omp.h>
#endif
#include <stdio.h>
#include <stdlib.h>

/*
opcionais: 
omp_set_num_threads(4) só funciona fora da região paralela
*/
/*
	se for usar um for, nao declare a variavel de iteração fora do bloco pragma. 
*/

int main () {
	
    #pragma omp parallel // num_threads(4) ->se quiser eu posso setar aqui e não em cima
	                    //posso botar também if condição
	{	
        int id = omp_get_thread_num();   // igual a 
		int total = omp_get_num_threads();
		int i;
		
		#pragma omp for      //como sao 4 threads, cada thread faz o numero de iteracoes /4. 
		for(i = 0; i < 20; i++)
			printf("\nEssa eh a thread numero %d de um total de %d.\n", id,total);
    }
	return 0;
}