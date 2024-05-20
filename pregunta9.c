#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int n = 20; 
    int a1 = 2; // Primer término
    int d = 2; // Diferencia común
    int mi_rango, num_procs;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &mi_rango);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    
    int terminos_p_procs = n / num_procs;
    int resto = n % num_procs;
    
    int inicio = mi_rango * terminos_p_procs + 1 ;
    int finr = inicio + terminos_p_procs - 1 ;
    if (mi_rango == num_procs - 1) 
        finr = n;

    MPI_Barrier(MPI_COMM_WORLD);

    printf("Proceso %d: ", mi_rango);
    for (int i = inicio; i <= finr; ++i) {
        int term = a1 + d * (i - 1); 
        printf("%d ", term);
    }
    printf("\n");

    MPI_Finalize();

    return 0;
}

