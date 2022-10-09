#include <omp.h>
#include <stdio.h>

int main() {
    int b = 10;
    omp_set_num_threads(24);
    #pragma omp parallel default(none) shared(b) 
    {
        int a = omp_get_thread_num();
        b = a;        
        printf("Hello world fro thread %d of %d. b = %d\n", omp_get_thread_num(), 
        omp_get_num_threads(), b);
    }
    printf("b = %d\n", b);
    return 0;
}