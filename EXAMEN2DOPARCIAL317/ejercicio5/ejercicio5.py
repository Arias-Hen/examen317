import numpy as np
from scipy.sparse import random, vstack
from multiprocessing import Pool

def generate_sparse_matrix(dim, density):
    return random(dim, dim, density=density, format='csr')

def multiply_row_by_matrix(row, B):
    return row.dot(B)

if __name__ == '__main__':
    matrix_dim = 1000
    matrix_density = 0.01

    with Pool() as pool:
        # Genera matrices dispersas A y B
        A = generate_sparse_matrix(matrix_dim, matrix_density)
        B = generate_sparse_matrix(matrix_dim, matrix_density)

        # Divide A en filas
        rows = [A.getrow(i) for i in range(A.shape[0])]

        # Multiplica cada fila de A por B en paralelo
        result = pool.starmap(multiply_row_by_matrix, [(row, B) for row in rows])

        # Combina los resultados en una matriz dispersa
        C = vstack(result)

# Obtener los índices de los elementos no cero
row, col = C.nonzero()

# Imprimir los elementos no cero y sus índices
for i in range(len(row)):
    print(f'({row[i]}, {col[i]}){C[row[i], col[i]]}\n')
