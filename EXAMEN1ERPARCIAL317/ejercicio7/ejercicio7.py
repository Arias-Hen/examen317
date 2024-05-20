#EJERCICIO 7
import random
import multiprocessing as mp

def monte_carlo_pi(n):
    dentro_circulo = 0
    for _ in range(n):
        x = random.random()
        y = random.random()
        if x**2 + y**2 <= 1:
            dentro_circulo += 1
    return dentro_circulo

def estimar_pi(num_muestras, num_procesos):
    grupo = mp.Pool(num_procesos)
    muestras_por_proceso = [num_muestras // num_procesos] * num_procesos
    for i in range(num_muestras % num_procesos):
        muestras_por_proceso[i] += 1

    resultados = grupo.map(monte_carlo_pi, muestras_por_proceso)
    total_dentro = sum(resultados)
    total_muestras = sum(muestras_por_proceso)

    estimacion_pi = 4 * (total_dentro / total_muestras)
    return estimacion_pi

if __name__ == '__main__':
    num_muestras = 10000000
    num_procesos = mp.cpu_count()

    pi_estimado = estimar_pi(num_muestras, num_procesos)
    print("Estimación de Pi:", pi_estimado)
