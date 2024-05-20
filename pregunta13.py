import multiprocessing

# Función de Fibonacci con memoización
def fibonacci(n, memo={}):
    if n in memo:
        return memo[n]
    if n <= 1:
        return n
    else:
        resultado = fibonacci(n-1, memo) + fibonacci(n-2, memo)
        memo[n] = resultado
        return resultado

# Función para calcular la secuencia de Fibonacci en un rango dado
def calcular_fibonacci_rango(inicio, fin):
    return [fibonacci(i) for i in range(inicio, fin)]

def main():
    num_terminos = 1000
    num_procesadores = multiprocessing.cpu_count()
    terminos_por_procesador = num_terminos // num_procesadores

    # Usar Pool de procesos para ejecutar en paralelo
    with multiprocessing.Pool(processes=num_procesadores) as pool:
        resultados = pool.starmap(calcular_fibonacci_rango, [(i*terminos_por_procesador, (i+1)*terminos_por_procesador) for i in range(num_procesadores)])

    # Unir resultados de todos los procesos
    secuencia_fibonacci = []
    for resultado in resultados:
        secuencia_fibonacci.extend(resultado)

    print("Secuencia de Fibonacci:")
    print(secuencia_fibonacci)

if __name__ == "__main__":
    main()

