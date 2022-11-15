#ifdef _OPENMP
    #include <omp.h>
#endif
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#define SIZE 320    //O SISTEMA COMEÇA A PERCEBER DIFERENÇA NO TEMPO COM UM SIZE = 150

void preenchermatriz(int matriz[SIZE][SIZE]);
void multiplicarserial(int matriz_a[SIZE][SIZE], int matriz_b[SIZE][SIZE], int matriz_c[SIZE][SIZE]);
void multiplicarparalelo(int matriz_a[SIZE][SIZE],int matriz_b[SIZE][SIZE], int matriz_c[SIZE][SIZE]);
void olamundo();

int main(int argc, char *argv[]){  //SE NAO FOR OLA MUNDO -> COMPILAR NORMAL - gcc -o olamundoparalelo olamundoparalelo.c
    //olamundo();
    struct timeval comeco_serial, fim_serial, comeco_paralelo, fim_paralelo;
    
    srand(time(NULL));
    int a_serial[SIZE][SIZE], b_serial[SIZE][SIZE], c_serial[SIZE][SIZE], a_paralelo[SIZE][SIZE], b_paralelo[SIZE][SIZE], c_paralelo[SIZE][SIZE];
    
    preenchermatriz(a_serial);
    preenchermatriz(b_serial);
    gettimeofday(&comeco_serial, NULL);
    multiplicarserial(a_serial,b_serial,c_serial);
    gettimeofday(&fim_serial, NULL);
    printf("\nTempo gasto na execução do programa serial: %f s\n",(double)(fim_serial.tv_usec - comeco_serial.tv_usec)/1000000 + (double)(fim_serial.tv_sec - comeco_serial.tv_sec));
    
    preenchermatriz(a_paralelo);
    preenchermatriz(b_paralelo);
    gettimeofday(&comeco_paralelo, NULL);
    multiplicarparalelo(a_paralelo, b_paralelo, c_paralelo);
    gettimeofday(&fim_paralelo, NULL);
    printf("\nTempo gasto na execução do programa paralelo: %f s\n",(double) (fim_paralelo.tv_usec - comeco_paralelo.tv_usec)/1e6 + (double) (fim_paralelo.tv_sec - comeco_paralelo.tv_sec));
    
    system("pause");
}

void preenchermatriz(int matriz[SIZE][SIZE]){
    for (int j = 0; j < SIZE; j++){
        for(int k = 0; k < SIZE; k++){
            matriz[j][k] = rand() % 16;  //preenche com um numero aleatório de 0 a 15
        }
    }
}

void multiplicarserial(int matriz_a[SIZE][SIZE],int matriz_b[SIZE][SIZE], int matriz_c[SIZE][SIZE]){
    int i,j,x;
    for (i = 0; i < SIZE; i++){              //percorrer a linha de A
        for (j = 0; j < SIZE; j++){          //percorrer a coluna de B

            matriz_c[i][j] = 0;
            for (x = 0; x < SIZE; x++){      //percorrer para preencher a matriz de produto
                matriz_c[i][j] += matriz_a[i][x] * matriz_b[x][j];
            }
        }
    }
}

void multiplicarparalelo(int a[SIZE][SIZE],int b[SIZE][SIZE], int c[SIZE][SIZE]){
    
    #pragma omp parallel 
    { 
        int i,j,x;
        #pragma omp for
            for(i = 0; i  < SIZE; i++){
                for(j = 0; j < SIZE; j++){
                    c[i][j] = 0;

                    for(x = 0; x < SIZE; x++){
                        c[i][j] += a[i][j] * b[x][j];
                    }
                }
            }       
    }
}

void olamundo(){       // COMPILAR COM gcc -o multimatrizparalelo multimatrizparalelo.c -fopenmp
    //omp_set_num_threads(numero-da-sua-escolha);
    int variavel = 35;
    #pragma omp parallel if (variavel > 30)
    {
    #ifdef _OPENMP
        int TOTAL = omp_get_num_threads();
        int ID = omp_get_thread_num();
    #endif
        printf("\nOlá. Essa é a thread numero %d de um total de %d threads.\n", ID,TOTAL);
    }
}