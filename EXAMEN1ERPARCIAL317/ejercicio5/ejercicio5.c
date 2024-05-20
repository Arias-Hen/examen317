#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int size, rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int tamano;
    if (rank == 0) {
        printf("Introduce el tamaño de la matriz y el vector: ");
        scanf("%d", &tamano);
    }

    MPI_Bcast(&tamano, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int nueva_matriz[tamano][tamano];
    int nuevo_vector[tamano];
    int resultado_parcial[tamano];

    if (rank == 0) {
        printf("Matriz:\n");
        for (int i = 0; i < tamano; i++) {
            nuevo_vector[i] = rand() % 10 + 1; // Números aleatorios entre 1 y 10
            for (int j = 0; j < tamano; j++) {
                nueva_matriz[i][j] = rand() % 10 + 1; // Números aleatorios entre 1 y 10
                printf("%d ", nueva_matriz[i][j]);
            }
            printf("\n");
        }

        printf("\nVector:\n");
        for (int i = 0; i < tamano; i++) {
            printf("%d\n", nuevo_vector[i]);
        }
        printf("\n");

        // Inicialización del resultado parcial con ceros
        for (int i = 0; i < tamano; i++) {
            resultado_parcial[i] = 0;
        }
    }

    MPI_Bcast(nuevo_vector, tamano, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = rank; i < tamano; i += size) {
        for (int j = 0; j < tamano; j++) {
            resultado_parcial[i] += nueva_matriz[i][j] * nuevo_vector[j];
        }
    }

    MPI_Reduce(resultado_parcial, nuevo_vector, tamano, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Resultado:\n");
        for (int i = 0; i < tamano; i++) {
            printf("%d\n", nuevo_vector[i]);
        }
    }

    MPI_Finalize();
    return 0;
}
