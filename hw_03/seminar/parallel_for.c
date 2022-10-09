#include <omp.h>
#include <stdio.h>

int main() {
    int N = 4;
    int sum = 0;
    int a[N], i;

    #pragma omp parallel for
    for (i = 0; i < N; i++) {
        a[i] = i;
        printf("iterate i = %3d by thread %3d \n", i, omp_get_thread_num());
    }

    for (i = 0; i < N; i++){
        printf("%d\t", a[i]);
    }        
    printf("\n");
    return 0;
}