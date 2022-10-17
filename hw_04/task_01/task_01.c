#include <stdio.h>
#include <stdlib.h>

const size_t N = 4;

void ZeroMatrix(int * A)
{
    for(size_t i=0; i<N; i++)
    {
        for(size_t j=0; j<N; j++)
        {
            A[i * N + j] = 0.0;
        }
    }
}

void RandomAdjMatrix(int * adj_matrix, int * answer) {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            adj_matrix[i * N + j] = rand() % 2;
            answer[i * N + j] = adj_matrix[i * N + j];
        }
    }
}


void CalcMatMulTime_ikj_opt_MY_01(int * A, int * B, int * C)
{
    size_t i, j, k;
    
    for (int i = 0; i < N; ++i)
    {
        int * c = C + i * N;
        for (int j = 0; j < N; ++j)
            c[j] = 0;
        for (int k = 0; k < N; ++k)
        {
            const int * b = B + k * N;
            int a = A[i*N + k];
            for (int j = 0; j < N; ++j)
                c[j] += a * b[j];
        }
    }
    
    return;

}

void printAdj(int * a) {
    printf("==================================================\n");
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            printf("%d ", a[i * N + j]);
        }
        printf("\n");
    }
    printf("==================================================\n");
}

int main() {    
    int *a, *b, *answer;
    a = (int*) malloc(N * N * sizeof(int));
    b = (int*) malloc(N * N * sizeof(int));
    answer = (int*) malloc(N * N * sizeof(int));
    ZeroMatrix(&answer[0]);
    RandomAdjMatrix(&a[0], &b[0]);       

    printAdj(&a[0]);

    int m;
    scanf("%d", &m); 
    // int m = 2; 
    m -= 1;

    for (size_t i = 0; i < m; ++i) {
        if (i % 2 == 0) {
            CalcMatMulTime_ikj_opt_MY_01(&a[0], &b[0], &answer[0]);
        }
        else {
            CalcMatMulTime_ikj_opt_MY_01(&a[0], &answer[0], &b[0]);
        }
    }

    if (m % 2 != 0) {
        printAdj(&answer[0]);
    }
    else {
        printAdj(&b[0]);
    }

    free(a);
    free(b);
    free(answer);

    return 0;
}