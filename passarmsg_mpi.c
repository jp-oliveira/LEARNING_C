#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <mpi.h>
int main(int argc, char* argv[]){
    int i,n,p, my_rank; //my_rank = o processo vigente. p = quantidade de processos
                        //i = para iterar no for. n = recebe o dado do usuario
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    int tag = 0;
    int local_n = 0; 

    if (my_rank == 0) {
        n = atoi(argv[1]);   //no 1 processo recebe o dado passado pelo usuario por linha de comando
        MPI_Send(&n, 1, MPI_INT, 1, tag, MPI_COMM_WORLD);  //envia o valor de n para o processo 1 - 4 argumento
        local_n = n;
        MPI_Recv(&local_n, 1, MPI_INT, my_rank - 1, tag, MPI_COMM_WORLD, &status);
    }

    else{
        MPI_Recv(&local_n, 1, MPI_INT, my_rank - 1, tag, MPI_COMM_WORLD, &status);
        local_n = local_n + my_rank;
        
        if(my_rank == p - 1)    // se for o ultimo processo - se forem 4 o ultimo é o 3. envia para o processo 0 
            MPI_Send(&local_n, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
        else
            MPI_Send(&local_n, 1, MPI_INT, my_rank + 1, tag, MPI_COMM_WORLD);
    }
    printf("Meu id: %d Received: %d \n", my_rank, local_n);
    MPI_Finalize();
}