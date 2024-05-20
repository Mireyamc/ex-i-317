#include <stdio.h>
#include <mpi.h>

#define N 4

void multiplicarMatrizVector(int matriz[N][N], int vector[N], int resultado_parcial[N / 2], int mi_rango, int num_procesos) {
    int inicio = mi_rango * (N / num_procesos);
    int fin = (mi_rango + 1) * (N / num_procesos);

    for (int i = inicio; i < fin; i++) {
        resultado_parcial[i - inicio] = 0;
        for (int j = 0; j < N; j++) {
            resultado_parcial[i - inicio] += matriz[i][j] * vector[j];
        }
    }
}

int main(int argc, char *argv[]) {
    int mi_rango, num_procesos;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &mi_rango);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procesos);

    if (N % num_procesos != 0) {
        if (mi_rango == 0) {
            printf("El número de procesos debe dividir exactamente el tamaño de la matriz.\n");
        }
        MPI_Finalize();
        return 0;
    }

    int matriz[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    int vector[N] = {1, 2, 3, 4};
    int resultado_parcial[N / num_procesos];
    int resultado[N];

    multiplicarMatrizVector(matriz, vector, resultado_parcial, mi_rango, num_procesos);

    MPI_Gather(resultado_parcial, N / num_procesos, MPI_INT, resultado, N / num_procesos, MPI_INT, 0, MPI_COMM_WORLD);

    if (mi_rango == 0) {
        printf("Resultado de la multiplicación:\n");
        for (int i = 0; i < N; i++) {
            printf("%d ", resultado[i]);
        }
        printf("\n");
    }

    MPI_Finalize();

    return 0;
}
