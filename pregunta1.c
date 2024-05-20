#include <stdio.h>

// Suma
void suma(int *a, int *b, int *resultado) {
    *resultado = *a + *b;
}

// Resta
void resta(int *a, int *b, int *resultado) {
    *resultado = *a - *b;
}

// Multiplicación basada en sumas
void multiplicacion(int *a, int *b, int *resultado) {
    *resultado = 0;
    for (int i = 0; i < *b; i++) {
        *resultado += *a;
    }
}

// División basada en restas
void division(int *a, int *b, int *resultado) {
    if (*b == 0) {
        printf("División por cero no permitida\n");
        return;
    }
    *resultado = 0;
    int resto = *a;
    while (resto >= *b) {
        resto -= *b;
        (*resultado)++;
    }
}

int main() {
    int a = 10;
    int b = 3;
    int resultado;
    
    // Suma
    suma(&a, &b, &resultado);
    printf("Suma: %d + %d = %d\n", a, b, resultado);
    
    // Resta
    resta(&a, &b, &resultado);
    printf("Resta: %d - %d = %d\n", a, b, resultado);
    
    // Multiplicación
    multiplicacion(&a, &b, &resultado);
    printf("Multiplicación: %d * %d = %d\n", a, b, resultado);
    
    // División
    division(&a, &b, &resultado);
    printf("División: %d / %d = %d\n", a, b, resultado);
    
    return 0;
}
	
