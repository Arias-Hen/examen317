#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define NUM_PUNTOS 1000000

int main(int argc, char *argv[]) {
	int rank, size;
	double x, y;
	int contador = 0;
	double pi;
	int total_contador;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	srand(rank);

	for (int i = 0; i < NUM_PUNTOS / size; i++) {
		x = (double)rand() / RAND_MAX;
		y = (double)rand() / RAND_MAX;
		if (x * x + y * y <= 1.0) {
			contador++;
		}
	}

	MPI_Reduce(&contador, &total_contador, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		pi = 4.0 * total_contador / NUM_PUNTOS;
		printf("Valor de pi: %lf\n", pi);
	}

	MPI_Finalize();
	return 0;
}
