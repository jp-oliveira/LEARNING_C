#ifdef _OPENMP
	#include <omp.h>
#endif
#include <stdio.h>
#include <stdlib.h>

int main () {
	
	int i;
	char palavra[10] = "festa";
    #pragma omp parallel private(i) shared(palavra) //firstprivate() e lastprivate()
	{
		int id = omp_get_thread_num();
		int total = omp_get_num_threads();
		for(i = 0; i < 3; i++)
			printf("\nEssa eh a thread numero %d de um total de %d.\n", id,total);
			
		printf("\n%s\n",palavra);
    }
	return 0;
}

// private - declarado fora e modificado dentro - nao inicializa dentro. O valor da variável original não é alterada ao final da região
//shared - declarado fora e apenas usado dentro mas sem modificar
//firstprivate - As variáveis serão inicializadas com o valor da variável compartilhada. exemplo, int incr = 0 fora do pragma e se eu der
//incr++ dentro do pragma x vezes, cada thread obtém sua própria cópia de incr com o valor inicial em 0
//lasprivate - o valor final de dentro do laço paralelo pode ser transmitido para uma variável compartilhada fora do laço
//default - Especifica o escopo default de variáveis que não foram listadas com nenhum escopo específico. o padrão é shared.
//reduction -  Quando é necessário acumular (ou outra operação) em uma única variável o resultado de várias threads
//ex: reduction(+: sum)

//pragma open for = olhar piparalelo.c
