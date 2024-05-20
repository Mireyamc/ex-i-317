#include <stdio.h>
#include <omp.h>

int main() {
    int n = 9;
    int a1 = 2; // Primer término
    int d = 2; // Diferencia común
    int M = 4; // Número de vectores
    int terms_per_vector = n / M;
    int vectors[M][terms_per_vector];

    #pragma omp parallel num_threads(M)
    {
        int thread_id = omp_get_thread_num();

        int start_index = thread_id * terms_per_vector + 1;
        int end_index = start_index + terms_per_vector - 1;
        if (thread_id == M - 1) // Si es el último hilo, ajustar el índice final
            end_index = n;

        for (int i = start_index; i <= end_index; ++i) {
            int term = a1 + d * (i - 1); // Calcular el término
            vectors[thread_id][i - start_index] = term;
        }
    } 
    //fin paralela

    // Imprimir 
    for (int i = 0; i < M; ++i) {
        printf("Vector %d: ", i + 1);
        for (int j = 0; j < terms_per_vector; ++j) {
            printf("%d ", vectors[i][j]);
        }
        printf("\n");
    }

    return 0;
}

