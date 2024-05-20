import multiprocessing
import math

def calcular_pi_parcial(inicio, fin, ancho):
    suma_local = 0.0
    for i in range(inicio, fin):
        x = (i + 0.5) * ancho
        suma_local += 4.0 / (1.0 + x * x)
    return suma_local

def calcular_pi(num_intervals, num_procesos):
    ancho = 1.0 / num_intervals
    chunk_size = num_intervals // num_procesos
    pool = multiprocessing.Pool(processes=num_procesos)

    tasks = [(i * chunk_size, (i + 1) * chunk_size, ancho) for i in range(num_procesos)]
    resultados = pool.starmap(calcular_pi_parcial, tasks)

    pi = sum(resultados) * ancho
    return pi

if __name__ == '__main__':
    num_intervals = 1000000  # Número de intervalos
    num_procesos = multiprocessing.cpu_count()  # Número de procesos igual al número de núcleos de CPU

    pi = calcular_pi(num_intervals, num_procesos)
    print(f"Valor aproximado de PI: {pi}")
