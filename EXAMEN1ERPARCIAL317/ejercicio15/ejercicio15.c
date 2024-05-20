#include <stdio.h>
#include <omp.h>

int main() {
    // Establecer el número de hilos que se usarán
    omp_set_num_threads(4);

    // Sección paralela
    #pragma omp parallel
    {
        // Cada hilo imprime "Hola Mundo"
        int thread_id = omp_get_thread_num();
        printf("Hola Mundo desde el hilo %d\n", thread_id);
    }

    return 0;
}
