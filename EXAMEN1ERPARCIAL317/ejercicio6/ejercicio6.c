#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define NUM_INTERVALOS 1000000

double f(double x) {
    return 4.0 / (1.0 + x * x);
}

int main(int argc, char *argv[]) {
    int rank, size;
    double suma_parcial = 0.0;
    double integral_parcial = 0.0;
    double integral_total;
    double inicio_intervalo, fin_intervalo;
    double ancho_intervalo;
    int i;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    ancho_intervalo = 1.0 / (double)NUM_INTERVALOS;

    inicio_intervalo = rank * (double)NUM_INTERVALOS / size * ancho_intervalo;
    fin_intervalo = (rank + 1) * (double)NUM_INTERVALOS / size * ancho_intervalo;

    for (i = 0; i < NUM_INTERVALOS / size; i++) {
        double x = inicio_intervalo + i * ancho_intervalo;
        suma_parcial += f(x);
    }

    integral_parcial = ancho_intervalo * suma_parcial;

    MPI_Reduce(&integral_parcial, &integral_total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Valor de pi: %lf\n", integral_total);
    }

    MPI_Finalize();
    return 0;
}
