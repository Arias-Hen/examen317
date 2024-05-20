#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int size, rank;
    int N, M;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        scanf("%d", &N);

        for (int i = 1; i < size; ++i) {
            MPI_Send(&N, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&M, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    } else {
        MPI_Recv(&N, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&M, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    int inicio = 2; 
    int fin = inicio + N * 2; 

    printf("Proceso %d: Serie generada: ", rank);
    for (int i = inicio; i < fin; i += 2) {
        printf("%d ", i);
    }
    printf("\n");

    MPI_Finalize();
    return 0;
}
