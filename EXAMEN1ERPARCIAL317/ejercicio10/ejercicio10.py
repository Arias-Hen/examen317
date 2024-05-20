#EJERCICIO 10

import multiprocessing as mp

def generar_serie(inicio, fin, paso, cola):
    serie = list(range(inicio, fin, paso))
    cola.put(serie)

def main():
    N = int(input("Ingrese el número de términos de la serie (N): "))
    M = int(input("Ingrese el número de vectores (procesadores) (M): "))

    paso = 2

    resultados = mp.Queue()

    procesos = []
    for i in range(M):
        inicio = i * N * paso + 2
        fin = inicio + N * paso
        p = mp.Process(target=generar_serie, args=(inicio, fin, paso, resultados))
        procesos.append(p)
        p.start()

    for proceso in procesos:
        proceso.join()

    series = []
    while not resultados.empty():
        series.append(resultados.get())

    for i, serie in enumerate(series):
        print(f"Proceso {i}: Serie generada: {' '.join(map(str, serie))}")

if __name__ == "__main__":
    main()
