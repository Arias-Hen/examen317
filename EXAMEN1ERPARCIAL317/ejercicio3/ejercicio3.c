#include <stdio.h>
#include <omp.h>

int main() {
    int a, b;
    int multiplicacion = 0;
    int division = 0;

    printf("Ingrese el valor de a: ");
    scanf("%d", &a);

    printf("Ingrese el valor de b: ");
    scanf("%d", &b);

    // Multiplicación por suma
    #pragma omp parallel for reduction(+:multiplicacion)
    for (int i = 0; i < b; i++) {
        multiplicacion += a;
    }

    // División por resta
    #pragma omp parallel for reduction(-:a) reduction(+:division)
    for (int i = 0; i < b; i++) {
        division++;
        a -= b;
    }

    printf("Multiplicación por suma: %d\n", multiplicacion);
    printf("División por resta: %d\n", division);

    return 0;
}
