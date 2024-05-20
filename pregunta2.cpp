#include <iostream>

// Suma
void suma(int* a, int* b, int* resultado) {
    *resultado = *a + *b;
}

// Resta
void resta(int* a, int* b, int* resultado) {
    *resultado = *a - *b;
}

// Multiplicación basada en sumas
void multiplicacion(int* a, int* b, int* resultado) {
    *resultado = 0;
    for (int i = 0; i < *b; i++) {
        *resultado += *a;
    }
}

// División basada en restas
int division(int* a, int* b, int* resultado) {
    if (*b == 0) {
        std::cout << "División por cero no permitida." << std::endl;
        return -1; // Retornar un valor especial para indicar error
    }
    *resultado = 0;
    int resto = *a;
    while (resto >= *b) {
        resto -= *b;
        (*resultado)++;
    }
    return 0; // Indicar éxito
}

int main() {
    int a = 10;
    int b = 3;
    int resultado;

    // Suma
    suma(&a, &b, &resultado);
    std::cout << "Suma: " << a << " + " << b << " = " << resultado << std::endl;

    // Resta
    resta(&a, &b, &resultado);
    std::cout << "Resta: " << a << " - " << b << " = " << resultado << std::endl;

    // Multiplicación
    multiplicacion(&a, &b, &resultado);
    std::cout << "Multiplicación: " << a << " * " << b << " = " << resultado << std::endl;

    // División
    int estado = division(&a, &b, &resultado);
    if (estado == 0) {
        std::cout << "División: " << a << " / " << b << " = " << resultado << std::endl;
    }

    return 0;
}
