#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int n = 20; // Número de términos (9 en este caso)
    int a1 = 2; // Primer término
    int d = 2; // Diferencia común
    int my_rank, num_procs;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    // Calcular el número de términos asignados a cada proceso
    int terms_per_process = n / num_procs;
    int remainder = n % num_procs;
    
    // Calcular el índice de inicio y fin para este proceso
    int start_index = my_rank * terms_per_process + 1 ;
    int end_index = start_index + terms_per_process - 1 ;
    if (my_rank == num_procs - 1) // Si es el último proceso, ajustar el índice final
        end_index = n;

    // Sincronizar la salida
    MPI_Barrier(MPI_COMM_WORLD);

    // Generar los términos de la serie para este proceso y mostrarlos
    printf("Proceso %d: ", my_rank);
    for (int i = start_index; i <= end_index; ++i) {
        int term = a1 + d * (i - 1); // Calcular el término
        printf("%d ", term);
    }
    printf("\n");

    MPI_Finalize();

    return 0;
}

