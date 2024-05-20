#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>


long long fibonacci(int n) {
    if (n <= 1) return n;
    long long a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return c;
}

int main(int argc, char* argv[]) {
    int rango, tamanio;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rango);
    MPI_Comm_size(MPI_COMM_WORLD, &tamanio);

    if (argc != 2) {
        if (rango == 0) {
            fprintf(stderr, "Uso: %s <n>\n", argv[0]);
        }
        MPI_Finalize();
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        if (rango == 0) {
            fprintf(stderr, "El valor de n debe ser positivo.\n");
        }
        MPI_Finalize();
        return 1;
    }

    if (rango == 0) {
        // Proceso MASTER
        MPI_Status estado;
        long long resultado;
        int i, rango_trabajador;

        for (i = 1; i <= n; i++) {
            rango_trabajador = (i - 1) % (tamanio - 1) + 1;
            MPI_Send(&i, 1, MPI_INT, rango_trabajador, 0, MPI_COMM_WORLD);
            MPI_Recv(&resultado, 1, MPI_LONG_LONG, rango_trabajador, 0, MPI_COMM_WORLD, &estado);
            printf("%lld ", resultado);
        }
 	printf("\n");

        for (i = 1; i < tamanio; i++) {
            int senal_terminacion = -1;
            MPI_Send(&senal_terminacion, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }

    } else {
        // Procesos SLAVE
        int tarea;
        long long resultado;
        MPI_Status estado;

        while (1) {
            MPI_Recv(&tarea, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &estado);
            if (tarea == -1) break;
            resultado = fibonacci(tarea);
            MPI_Send(&resultado, 1, MPI_LONG_LONG, 0, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}

