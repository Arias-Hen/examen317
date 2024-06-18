#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define MATRIX_SIZE 1000
#define SPARSITY 0.01 // Porcentaje de elementos no cero

typedef struct {
    int rows;
    int cols;
    int nnz; // number of non-zero elements
    double *values;
    int *col_index;
    int *row_ptr;
} CSRMatrix;

CSRMatrix* create_csr_matrix(int rows, int cols, int max_nnz) {
    CSRMatrix mat = (CSRMatrix) malloc(sizeof(CSRMatrix));
    mat->rows = rows;
    mat->cols = cols;
    mat->nnz = 0; // Initially no non-zero elements
    mat->values = (double*) malloc(max_nnz * sizeof(double));
    mat->col_index = (int*) malloc(max_nnz * sizeof(int));
    mat->row_ptr = (int*) malloc((rows + 1) * sizeof(int));
    return mat;
}

void free_csr_matrix(CSRMatrix *mat) {
    free(mat->values);
    free(mat->col_index);
    free(mat->row_ptr);
    free(mat);
}

void generate_random_csr_matrix(CSRMatrix *mat, double sparsity) {
    int max_nnz = mat->rows * mat->cols * sparsity;
    int nnz = 0;
    mat->row_ptr[0] = 0;

    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            if ((double)rand() / RAND_MAX <= sparsity) {
                if (nnz >= max_nnz) {
                    break; // No more elements can be added
                }
                mat->values[nnz] = (double)(rand() % 100) / 10.0; // Valor random entre 0.0 y 9.9
                mat->col_index[nnz] = j;
                nnz++;
            }
        }
        mat->row_ptr[i + 1] = nnz;
    }
    mat->nnz = nnz;
}

CSRMatrix* multiply_csr_matrices(const CSRMatrix *A, const CSRMatrix *B) {
    if (A->cols != B->rows) {
        fprintf(stderr, "Matrix dimensions do not match for multiplication\n");
        exit(EXIT_FAILURE);
    }

    int max_nnz = A->nnz * B->nnz;
    int row_ptr = (int) calloc((A->rows + 1), sizeof(int));
    int col_index = (int) malloc(max_nnz * sizeof(int));
    double values = (double) malloc(max_nnz * sizeof(double));

    int nnz = 0;

    #pragma omp parallel
    {
        int local_row_ptr = (int) calloc((A->rows + 1), sizeof(int));
        int local_col_index = (int) malloc(max_nnz * sizeof(int));
        double local_values = (double) malloc(max_nnz * sizeof(double));
        int local_nnz = 0;

        #pragma omp for schedule(dynamic)
        for (int i = 0; i < A->rows; i++) {
            int row_start = A->row_ptr[i];
            int row_end = A->row_ptr[i + 1];

            for (int j = row_start; j < row_end; j++) {
                int col_A = A->col_index[j];
                double val_A = A->values[j];

                int col_start = B->row_ptr[col_A];
                int col_end = B->row_ptr[col_A + 1];

                for (int k = col_start; k < col_end; k++) {
                    int col_B = B->col_index[k];
                    double val_B = B->values[k];

                    local_values[local_nnz] = val_A * val_B;
                    local_col_index[local_nnz] = col_B;
                    local_nnz++;
                }
            }

            local_row_ptr[i + 1] = local_nnz;
        }

        #pragma omp critical
        {
            for (int i = 0; i < A->rows; i++) {
                row_ptr[i + 1] += local_row_ptr[i + 1];
            }
            for (int i = 0; i < local_nnz; i++) {
                values[nnz + i] = local_values[i];
                col_index[nnz + i] = local_col_index[i];
            }
            nnz += local_nnz;
        }

        free(local_row_ptr);
        free(local_col_index);
        free(local_values);
    }

    for (int i = 1; i <= A->rows; i++) {
        row_ptr[i] += row_ptr[i - 1];
    }

    CSRMatrix *C = create_csr_matrix(A->rows, B->cols, nnz);
    C->values = (double*) realloc(values, nnz * sizeof(double));
    C->col_index = (int*) realloc(col_index, nnz * sizeof(int));
    C->row_ptr = row_ptr;
    C->nnz = nnz;

    return C;
}

void print_csr_matrix(const CSRMatrix *mat) {
    #pragma omp parallel for
    for (int i = 0; i < mat->rows; i++) {
        int row_start = mat->row_ptr[i];
        int row_end = mat->row_ptr[i + 1];
        #pragma omp critical
        {
            for (int j = row_start; j < row_end; j++) {
                printf("value: %f, col_index: %d, row: %d\n", mat->values[j], mat->col_index[j], i);
            }
        }
    }

    printf("row_ptr:\n");
    for (int i = 0; i <= mat->rows; i++) {
        printf("row_ptr[%d]: %d\n", i, mat->row_ptr[i]);
    }
}

int main() {
    srand(time(NULL));

    // Generar matrices A y B
    CSRMatrix *A = create_csr_matrix(MATRIX_SIZE, MATRIX_SIZE, (int)(MATRIX_SIZE * MATRIX_SIZE * SPARSITY));
    CSRMatrix *B = create_csr_matrix(MATRIX_SIZE, MATRIX_SIZE, (int)(MATRIX_SIZE * MATRIX_SIZE * SPARSITY));

    generate_random_csr_matrix(A, SPARSITY);
    generate_random_csr_matrix(B, SPARSITY);

    // Multiplicar matrices
    double start_time = omp_get_wtime();
    CSRMatrix *C = multiply_csr_matrices(A, B);
    double end_time = omp_get_wtime();

    printf("Tiempo de multiplicación: %f segundos\n", end_time - start_time);

    // Imprimir resultados de la matriz C de manera paralela
    print_csr_matrix(C);

    // Liberar memoria
    free_csr_matrix(A);
    free_csr_matrix(B);
    free_csr_matrix(C);

    return 0;
}