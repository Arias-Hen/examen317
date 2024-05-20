#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 10 // Número de términos de la secuencia de Fibonacci

int fibonacci(int n) {
    if (n <= 1)
        return n;
    else
        return fibonacci(n - 1) + fibonacci(n - 2);
}

int main(int argc, char **argv) {
    int rank, size;
    int result;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        fprintf(stderr, "Se necesitan al menos dos procesos para este ejemplo.\n");
        MPI_Finalize();
        return EXIT_FAILURE;
    }

    if (rank == 0) { // Proceso maestro
        for (int i = 0; i < N; i++) {
            int term;
            MPI_Recv(&term, 1, MPI_INT, MPI_ANY_SOURCE, i, MPI_COMM_WORLD, &status);
            printf("Término %d: %d\n", i + 1, term);
        }
    }
    else { // Procesos esclavos
        for (int i = rank - 1; i < N; i += size - 1) {
            int term = fibonacci(i);
            MPI_Send(&term, 1, MPI_INT, 0, i, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}
