#include <stdio.h>
#include <omp.h>

int main() {
    int num_procs = 5;
    #pragma omp parallel num_threads(num_procs)
    {
        int tid = omp_get_thread_num();
        printf("Hola mundo %d\n", tid);
    }
    
    return 0;
}
