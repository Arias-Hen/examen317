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
    int temp_a = a;  

    #pragma omp parallel
    {
        #pragma omp single
        {
            while (temp_a >= b) {
                temp_a -= b;
                division++;
            }
        }
    }

    printf("Multiplicación por suma: %d\n", multiplicacion);
    printf("División por resta: %d\n", division);

    return 0;
}
