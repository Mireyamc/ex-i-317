from multiprocessing import *

def generate_series(start, end, queue):
    result = []
    for i in range(start, end):
        result.append((i + 1) * 2)
    queue.put(result)

if __name__ == '__main__':
    N = 24  # Número de términos en la serie
    num_processes = 6  # Número de procesos

    terminos_por_proceso = N // num_processes
    queue = Queue()
    processes = []

    # Crear y arrancar los procesos
    for rank in range(num_processes):
        inicio = rank * terminos_por_proceso
        fin = inicio + terminos_por_proceso
        if rank == num_processes - 1:
            fin = N
        p = Process(target=generate_series, args=(inicio, fin, queue))
        processes.append(p)
        p.start()

    # Recopilar los resultados
    results = []
    for _ in range(num_processes):
        results.append(queue.get())

    # Esperar a que todos los procesos terminen
    for p in processes:
        p.join()

    # Imprimir los resultados en el formato deseado
    print("Salida:")
    vector_num = 1
    for result in results:
        print(f"Vector {vector_num}: {' '.join(map(str, result))}")
        vector_num += 1
