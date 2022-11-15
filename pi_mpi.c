#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

int main(int argc, char* argv[]){
    struct timeval comeco_serial, fim_serial, comeco_paralelo, fim_paralelo;
    if (atoi(argv[2]) != 1){

        gettimeofday(&comeco_serial, NULL);
        double h,sum, mypi,x;
        int i,n;
           
        n = atoi(argv[1]);
        h = 1.0 / (double) n;
        sum = 0.0;
        
        for (i = 1; i <= n; i ++) {
            x = h * ((double)i - 0.5);
            sum += 4.0 / (1.0 + x*x);
        }
        mypi = h * sum;
        gettimeofday(&fim_serial, NULL);
        printf("\nTempo gasto na execução do programa serial:   %f s\n",(double)(fim_serial.tv_usec - comeco_serial.tv_usec)/1000000 + (double)(fim_serial.tv_sec - comeco_serial.tv_sec));
        printf("pi com precisão %d é igual à = %f\n",n,mypi);
    }
    else{
        #include<mpi.h>
        gettimeofday(&comeco_serial, NULL);        
        double h,sum, mypi;           //p é numero de processos
        int inicio, fim, i,n, n_bar,p, my_rank; //i = para iterar no for. n = recebe o dado do usuario
        int tag = 0; //o parametro tag é fixo para os sends e receives        

        MPI_Status status;
        MPI_Init(&argc, &argv);
        MPI_Comm_size(MPI_COMM_WORLD, &p);
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
         
        if (my_rank == 0) {
            n = atoi(argv[1]);       //pega o valor de n pra que todos os processos peguem o valor de n no for abaixo
            h = 1.0 / (double) n;   //h passado para todos os processos

            for (i=1; i<p; i++){
                MPI_Send(&n, 1, MPI_INT, i, tag, MPI_COMM_WORLD); //envia o valor de n para todos os outros processos -4º argumento
                MPI_Send(&h, 1, MPI_DOUBLE, i, tag, MPI_COMM_WORLD); //envia o valor de h para todos os outros processos -4º argumento
            }
        }
        else{
            MPI_Recv(&n, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status); //todos os processos recebem o valor de n do processo 0
            MPI_Recv(&h, 1, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD, &status); //todos os processos recebem o valor de h do processo 0
        }
        //printf("Meu id: %d Received: %d \n", my_rank, n);
        //printf("Meu h: %f \n",h);
        
        n_bar = n/p;    //divide a precisão de n pelo numero de processos p/ cada processo ter +/- o mesmo trabalho
        inicio = my_rank * n_bar;
        fim = (my_rank + 1) * n_bar;
        sum = 0.0;
        double x = 0.0;   //variavel temporaria para cada processo
        double local_sum = 0.0;
        for (i = inicio; i < fim; i++){
            x = h * ((double)i - 0.5);
            sum +=  4.0 / (1.0 + x*x);
        }
        if (my_rank != 0) {
            MPI_Send(&sum, 1, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD); //todos os outros processo mandam sum p/ 0
        }
        else{
            for(i = 1; i < p; i++){
                MPI_Recv(&local_sum, 1, MPI_DOUBLE, i, tag, MPI_COMM_WORLD, &status); //recebe o valor de local_sum do processo 0
                //printf("Processo %d enviou %f\n", i, local_sum);
                sum += local_sum;
            }
            gettimeofday(&fim_serial, NULL);
            printf("\nTempo gasto na execução do programa paralelo:   %f s\n",(double)(fim_serial.tv_usec - comeco_serial.tv_usec)/1000000 + (double)(fim_serial.tv_sec - comeco_serial.tv_sec));
            printf("Pi com precisão %d é: %f\n", n, sum * h);
        }
    MPI_Finalize();
    } 
    return 0;
}