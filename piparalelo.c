#ifdef _OPENMP
	#include <omp.h>
#endif
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

//lembrando: argc conta o numero de argumentos passados quando chama o programa, e argv um ponteiro para os parametros
//linhas de comando.
int main(int argc, char *argv[]){
    int n, i;
    struct timeval comeco_serial, fim_serial, comeco_paralelo, fim_paralelo;
    double mypi, h, sumserial, sumparalela, x;

    n = atoi(argv[1]);
    h = 1.0 / (double) n; 
    sumserial = sumparalela = 0.0;

	//srand(time(NULL));
	/*
    gettimeofday(&comeco_serial, NULL);
    
	for (i = 1; i <= n; i++) {
        x = h * ((double) i - 0.5);
        sumserial += 4.0 / (1.0 + x*x);
    }
    mypi = h * sumserial;
    gettimeofday(&fim_serial, NULL);

    printf("\nTempo gasto no programa serial:   %lf s\n",(double) (fim_serial.tv_usec - comeco_serial.tv_usec)/1e6 + (double) (fim_serial.tv_sec - comeco_serial.tv_sec));
    printf("pi is approximately %.16f com a precisao %d\n", mypi, n);
	*/
	
    double ajuda = 0.0;
    gettimeofday(&comeco_paralelo, NULL);
    #pragma omp parallel private(i,x,ajuda) shared(sumparalela) //reduction (+:sumparalela)
    {                                                           //comente o shared e descomente reduction para reduction  
        #pragma omp for
            for(i = 1; i <= n; i++){
                x = h * ((double) i - 0.5);
                ajuda += 4.0 / (1.0 + x*x);                     //comente para reduction
                //sumparalela += 4.0 / (1.0 + x*x);             //nao comente para reduction
            }
            #pragma omp critical                               //comente para reduction
            sumparalela = sumparalela + ajuda;                //comente para reduction
    }

    mypi = (h * sumparalela);
    gettimeofday(&fim_paralelo, NULL);
    printf("\nTempo gasto no programa paralelo: %f s\n",(double) (fim_paralelo.tv_usec - comeco_paralelo.tv_usec)/1e6 + (double) (fim_paralelo.tv_sec - comeco_paralelo.tv_sec));
    printf("pi is approximately %.16f com a precisao %d\n", mypi, n);
    
	return 0;
}