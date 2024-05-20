#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int tamano;
    printf("Introduce el tamaño de la matriz y el vector: ");
    scanf("%d", &tamano);

    int nueva_matriz[tamano][tamano];
    int nuevo_vector[tamano];
    int nuevo_resultado[tamano];

    printf("Matriz:\n");
    for (int i = 0; i < tamano; i++) {
        nuevo_vector[i] = rand() % 10 + 1; 
        for (int j = 0; j < tamano; j++) {
            nueva_matriz[i][j] = rand() % 10 + 1; 
            printf("%d ", nueva_matriz[i][j]); 
        }
        printf("\n");
    }

    printf("\nVector:\n");
    for (int i = 0; i < tamano; i++) {
        printf("%d\n", nuevo_vector[i]);
    }
    
    for (int i = 0; i < tamano; i++) {
        nuevo_resultado[i] = 0;
    }

#pragma omp parallel for
    for (int i = 0; i < tamano; i++) {
        for (int j = 0; j < tamano; j++) {
            nuevo_resultado[i] += nueva_matriz[i][j] * nuevo_vector[j];
        }
    }

    printf("\nResultado:\n");
    for (int i = 0; i < tamano; i++) {
        printf("%d\n", nuevo_resultado[i]);
    }

    return 0;
}
