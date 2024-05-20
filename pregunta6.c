#include <stdio.h>
#include <mpi.h>

double f(double x) {
    return 4.0 / (1.0 + x * x);
}

int main(int argc, char *argv[]) {
    int mi_rango, num_procesos, n = 1000000, i;
    double a = 0.0, b = 1.0, h, suma, x;
    double mi_suma, total_suma;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &mi_rango);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procesos);

    h = (b - a) / n;
    mi_suma = 0.0;

    for (i = mi_rango; i < n; i += num_procesos) {
        x = a + i * h + h / 2.0;
        mi_suma += f(x);
    }

    mi_suma *= h;

    MPI_Reduce(&mi_suma, &total_suma, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (mi_rango == 0) {
        printf("El valor aproximado de PI es: %.16f\n", total_suma);
    }

    MPI_Finalize();

    return 0;
}
