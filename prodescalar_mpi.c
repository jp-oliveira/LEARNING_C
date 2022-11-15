#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char* argv[]){

    double *x, *y, *local_x, *local_y;
    int n_bar; /* = n/p */
    double dot, local_dot;
    int p, my_rank, i, n;
    MPI_Status status;
    int tag = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    
    if (my_rank == 0) {
    
        n = atoi(argv[1]);
        x = (double *) calloc(n, sizeof(double));  //aloca memoria para os vetores
        y = (double *) calloc(n, sizeof(double));
        
        for (i=0; i<n; i++) {   //preencheu os vetores no 1 processo - myrank == 0
            x[i] = 1.0; 
            y[i] = 1.0;
        }
        for (i=1; i<p; i++){
            MPI_Send(&n, 1, MPI_INT, i, tag, MPI_COMM_WORLD);  //envia o valor de n para todos os outros processos
        }
    }
    else{
        MPI_Recv(&n, 1, MPI_INT, 0, tag, MPI_COMM_WORLD, &status); //recebe o valor de n do processo 0
    }
    printf("Meu id: %d Received: %d \n", my_rank, n);

    // Criação dos vetores locais - não tem necessidade do processo 0 criar o vetor local também. é desnecessário
    n_bar = n/p;  //divide o valor passado por linha de comando pelo numero de processo para cada processo fazer aprox o mesmo trabalho
    local_x = (double *) calloc(n_bar, sizeof(double));
    local_y = (double *) calloc(n_bar, sizeof(double));

    // Envio dos vetores para todos os processos
    if (my_rank == 0) {
        for (i=1; i<p; i++) {
            MPI_Send(&(x[i*n_bar]), n_bar, MPI_DOUBLE, i, tag, MPI_COMM_WORLD);
            MPI_Send(&(y[i*n_bar]), n_bar, MPI_DOUBLE, i, tag, MPI_COMM_WORLD);
        }
        for (i=0; i<n_bar; i++) {
            local_x[i] = x[i];
            local_y[i] = y[i];
        }
    }
    else {
        MPI_Recv(local_x, n_bar, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD, &status);
        MPI_Recv(local_y, n_bar, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD, &status);
    }

    /* Calcula o produto escalar local -Se o processo 0 não tivesse preenchido também, teria que fazer um if tanto em cima
    quanto aqui embaixo. Então, ele preenche desnecessariamente no processo 0 para não criar um if a mais. */
    
    local_dot = 0.0;
    for (i = 0; i < n_bar; i++){
        local_dot += local_x[i] * local_y[i];
    }
    free(local_x);
    free(local_y); 

    if (my_rank != 0) {
        MPI_Send(&local_dot, 1, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD);
    }
    else {
        for (i=1; i<p; i++) {
            MPI_Recv(&dot, 1, MPI_DOUBLE, i, tag, MPI_COMM_WORLD, &status);
            local_dot += dot;
        }
    }

    if (my_rank == 0) 
        printf("valor final = %f \n", local_dot);
    
    MPI_Finalize();
}

double dot_product(double x[], double y[], int n){
    int i;
    double result =0.0;
    for (i = 0; i < n; i++) {
        result += x[i] * y[i];
    }
    return result;
}