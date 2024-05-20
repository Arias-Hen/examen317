#include <stdio.h>

// Función para sumar dos números
int sumar(int *a, int *b) {
    return (*a) + (*b);
}

// Función para restar dos números
int restar(int *a, int *b) {
    return (*a) - (*b);
}

// Función para multiplicar dos números utilizando sumas repetidas
int multiplicar(int *a, int *b) {
    int resultado = 0;
    for (int i = 0; i < (*b); i++) {
        resultado = sumar(&resultado, a);
    }
    return resultado;
}

// Función para dividir dos números utilizando restas repetidas
int dividir(int *a, int *b) {
    int cociente = 0;
    int dividendo = *a;
    int divisor = *b;

    while (dividendo >= divisor) {
        dividendo = restar(&dividendo, &divisor);
        cociente++;
    }

    return cociente;
}

int main() {
    int num1, num2;

    printf("Ingrese el primer número: ");
    scanf("%d", &num1);

    printf("Ingrese el segundo número: ");
    scanf("%d", &num2);

    printf("Suma: %d\n", sumar(&num1, &num2));
    printf("Resta: %d\n", restar(&num1, &num2));
    printf("Multiplicación: %d\n", multiplicar(&num1, &num2));
    printf("División: %d\n", dividir(&num1, &num2));

    return 0;
}
