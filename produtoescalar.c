#ifdef _OPENMP
    #include <omp.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define SIZE 500000

int main(int argc, char * argv[]){

    double soma = 0.0, aux = 0.0;
    double a[SIZE], b[SIZE];
    int n = SIZE, i; 
    struct timeval comeco_serial, fim_serial, comeco_paralelo, fim_paralelo;
    
    for(int i = 0; i < n; i++){  //preenchimento dos vetores com quaisquer numeros
        a[i] = i * 1.0;
        b[i] = i * 1.0;
    }

    gettimeofday(&comeco_serial, NULL);
    for(i = 0; i < n; i++){
        soma += a[i] * b[i]; 
    }    
    gettimeofday(&fim_serial, NULL);
    printf("\nTempo gasto na execução do programa serial:   %fs\n",(double)(fim_serial.tv_usec - comeco_serial.tv_usec)/1000000 + (double)(fim_serial.tv_sec - comeco_serial.tv_sec));
    printf("O produto escalar  serial gerado foi de   %.2f\n", soma);

    double ajuda = 0.0;
    gettimeofday(&comeco_paralelo, NULL);
    #pragma omp parallel shared(n, a, b) private(i, ajuda) reduction (+:aux) 
    {                                             
        #pragma omp for
            for(i = 0; i < n; i++){
                ajuda += a[i] * b[i];        //comente para reduction
                //aux += a[i] * b[i];        //nao comente para reduction
            }
            #pragma omp critical             //comente para reduction
                aux = aux + ajuda;           //commente para reduction
    }
    gettimeofday(&fim_paralelo, NULL);

    printf("\nTempo gasto na execução do programa paralelo: %f s\n",(double) (fim_paralelo.tv_usec - comeco_paralelo.tv_usec)/1e6 + (double) (fim_paralelo.tv_sec - comeco_paralelo.tv_sec));
    printf("O produto escalar paralelo gerador foi de %.2f\n",aux);  
}