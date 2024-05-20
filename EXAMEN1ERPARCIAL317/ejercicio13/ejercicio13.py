#EJERCICIO 13

import multiprocessing as mp

def secuencia_fibonacci_rango(inicio, fin):
    secuencia_fibonacci = [0, 1]
    for i in range(2, fin):
        siguiente_fib = secuencia_fibonacci[-1] + secuencia_fibonacci[-2]
        secuencia_fibonacci.append(siguiente_fib)
    return secuencia_fibonacci[inicio:fin]

def fibonacci_paralelo(num_terminos, num_procesos):
    grupo = mp.Pool(num_procesos)
    terminos_por_proceso = [num_terminos // num_procesos] * num_procesos

    # Ajustar el número de términos por proceso para los primeros num_terminos % num_procesos procesos
    for i in range(num_terminos % num_procesos):
        terminos_por_proceso[i] += 1

    resultados = grupo.starmap(secuencia_fibonacci_rango, [(i * (num_terminos // num_procesos), (i+1) * (num_terminos // num_procesos)) for i in range(num_procesos)])
    grupo.close()
    grupo.join()

    secuencia_fibonacci = []
    for resultado in resultados:
        secuencia_fibonacci.extend(resultado)
    return secuencia_fibonacci

if __name__ == '__main__':
    num_terminos = 1000
    num_procesos = mp.cpu_count()

    secuencia_fibonacci = fibonacci_paralelo(num_terminos, num_procesos)
    print("Secuencia de Fibonacci generada:", secuencia_fibonacci)
