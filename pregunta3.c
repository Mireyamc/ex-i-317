#include <stdio.h>
#include <omp.h>

// Multiplicación basada en sumas
int multiplicacion(int a, int b) {
    int resultado = 0;
    #pragma omp parallel for reduction(+:resultado)
    for (int i = 0; i < b; i++) {
        resultado += a;
    }
    return resultado;
}

// División basada en restas
int division(int a, int b) {
    if (b == 0) {
        printf("División por cero no permitida\n");
        return -1;
    }
    int resultado = 0;
    int resto = a;
    #pragma omp parallel
    {
        while (resto >= b) {
            #pragma omp critical
            {
                resto -= b;
                resultado++;
            }
        }
    }
    return resultado;
}

int main() {
    int a = 10;
    int b = 3;

    // Multiplicación
    int resultado_multiplicacion = multiplicacion(a, b);
    printf("Multiplicación: %d * %d = %d\n", a, b, resultado_multiplicacion);

    // División
    int resultado_division = division(a, b);
    if (resultado_division != -1) {
        printf("División: %d / %d = %d\n", a, b, resultado_division);
    }

    return 0;
}
