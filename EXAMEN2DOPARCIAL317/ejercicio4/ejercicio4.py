from scipy.sparse import random as sparse_random

# Crear una matriz dispersa aleatoria de 1000x1000 con una densidad de 0.01
A = sparse_random(1000, 1000, density=0.01, format='csr')
B = sparse_random(1000, 1000, density=0.01, format='csr')

# Multiplicar las matrices
C = A.dot(B)

print(C)