#include <stdio.h>
#include <omp.h>

int main() {
    int n = 9; // Número de términos (9 en este caso)
    int a1 = 2; // Primer término
    int d = 2; // Diferencia común
    int M = 4; // Número de vectores (ajusta según tus necesidades)

    // Calcular el número de términos asignados a cada vector
    int terms_per_vector = n / M;

    // Arreglo para almacenar los vectores
    int vectors[M][terms_per_vector];

    // Iniciar la sección paralela
    #pragma omp parallel num_threads(M)
    {
        // Obtener el ID del hilo
        int thread_id = omp_get_thread_num();

        // Calcular el índice de inicio y fin para este hilo
        int start_index = thread_id * terms_per_vector + 1;
        int end_index = start_index + terms_per_vector - 1;
        if (thread_id == M - 1) // Si es el último hilo, ajustar el índice final
            end_index = n;

        // Generar los términos de la serie para este hilo
        for (int i = start_index; i <= end_index; ++i) {
            int term = a1 + d * (i - 1); // Calcular el término
            vectors[thread_id][i - start_index] = term;
        }
    } // Fin de la sección paralela

    // Imprimir los vectores en orden
    for (int i = 0; i < M; ++i) {
        printf("Vector %d: ", i + 1);
        for (int j = 0; j < terms_per_vector; ++j) {
            printf("%d ", vectors[i][j]);
        }
        printf("\n");
    }

    return 0;
}

