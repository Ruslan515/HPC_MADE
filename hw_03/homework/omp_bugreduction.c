#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void dotprod(float * a, float * b, size_t N, float * sum)
{
    int i, tid;
    float sum_th = 0.0;

    #pragma omp parallel for shared (N, a, b) private (i, tid) reduction(+:sum_th)
        for (i = 0; i < N; ++i)
        {
            tid = omp_get_thread_num();
            sum_th += a[i] * b[i];
            printf("tid = %d i = %d\n", tid, i);
        }

    *sum = sum_th;
}

int main (int argc, char *argv[])
{
    const size_t N = 3;
    int i;
    float sum;
    float a[N], b[N];


    for (i = 0; i < N; ++i)
    {
        a[i] = b[i] = (double)i;
    }

    sum = 0.0;
    
    dotprod(a, b, N, &sum);

    printf("Sum = %f\n",sum);

    return 0;
}