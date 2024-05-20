from multiprocessing import *

def generar_s(ini, fin_r, cola_s):
    resultado = []
    for i in range(ini, fin_r):
        resultado.append((i + 1) * 2)
    queue.put(resultado)

if __name__ == '__main__':
    N = 24  
    num_processes = 6  

    terminos_por_proceso = N 
    queue = queue()
    procesos = []

    for rango in range(num_processes):
        inicio = rango * terminos_por_proceso
        fin = inicio + terminos_por_proceso
        if rango == num_processes - 1:
            fin = N
        p = Process(target=generar_s, args=(inicio, fin, queue))
        procesos.append(p)
        p.start()

    resultados = []
    for _ in range(num_processes):
        resultados.append(queue.get())

    for p in procesos:
        p.join()

    print("Salida:")
    vector_num = 1
    for resultado in resultados:
        print(f"Vector {vector_num}: {' '.join(map(str, resultado))}")
        vector_num += 1
