// N == 1024        m == 2
// Worked on 12 threads, time elapsed = 4.856723 seconds
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

const int N = 1024;

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

void RandomAdjMatrix(int * adj_matrix, int * answer, int * temp) {
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            adj_matrix[i * N + j] = rand() % 2;
            answer[i * N + j] = adj_matrix[i * N + j];
            temp[i * N + j] = adj_matrix[i * N + j];
        }
    }
}


void CalcMatMulTime_ikj_opt_with_pragam(int * A, int * B, int * C)
{
    size_t i, j, k;
    
    #pragma omp parallel for shared(A, B, C)
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

void CalcMatMulTime_ikj_opt_without_pragam(int * A, int * B, int * C)
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

int compareAdjs(int * a, int *b) {
    printf("==================== Comapre ==============================\n");
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            if (a[i * N + j] != b[i * N + j]) {
                printf("not eq in i == %zu, j == %zu", i, j);
                return 0;
            }
        }        
    }
    printf("==================== End comapre ==============================\n");
    return 1;
}

int find_count_path() {        

    int *a, *b, *c, *answer_pragma, *answer_without_pragma;
    a = (int*) malloc(N * N * sizeof(int));
    b = (int*) malloc(N * N * sizeof(int)); 
    c = (int*) malloc(N * N * sizeof(int));
    answer_pragma = (int*) malloc(N * N * sizeof(int));
    answer_without_pragma = (int*) malloc(N * N * sizeof(int));

    // ============================ Start with pragma ===========================
    ZeroMatrix(&answer_pragma[0]);
    RandomAdjMatrix(&a[0], &b[0], &c[0]);

    // printAdj(&a[0]);

    int m;
    printf("intput m: ");
    scanf("%d", &m); 
    // int m = 2; 
    m -= 1;
    
    double start, end;
    start = omp_get_wtime();
    
    for (size_t i = 0; i < m; ++i) {
        if (i % 2 == 0) {
            CalcMatMulTime_ikj_opt_with_pragam(&a[0], &b[0], &answer_pragma[0]);
        }
        else {
            CalcMatMulTime_ikj_opt_with_pragam(&a[0], &answer_pragma[0], &b[0]);
        }
    }
    
    end = omp_get_wtime();

    printf("With pragma \n N == %d\t m == %d\n Используется %d нитей \n Время выполнения(сек) == %f seconds\n", \
        N, m, omp_get_max_threads(), (end-start));
    // ============================ End with pragma ===========================


    // ============================ Start without pragma ===========================
    ZeroMatrix(&answer_without_pragma[0]);    

    // printAdj(&a[0]);
        
    start = omp_get_wtime();
    for (size_t i = 0; i < m; ++i) {
        if (i % 2 == 0) {
            CalcMatMulTime_ikj_opt_without_pragam(&a[0], &c[0], &answer_without_pragma[0]);
        }
        else {
            CalcMatMulTime_ikj_opt_without_pragam(&a[0], &answer_without_pragma[0], &c[0]);
        }
    }    
    end = omp_get_wtime();

    printf("Without pragma \n N == %d\t m == %d\n Время выполнения(сек) == %f seconds\n", N, m, (end-start));
    // ============================ End without pragma ===========================

    if (m % 2 != 0) {        
        // compare answer_pragma and answer_without_pragma
        int res = compareAdjs(&answer_pragma[0], &answer_without_pragma[0]);
        if (res == 0) {
            printf("NOT EQ");
        }
        else {
            printf("All good!)\n");
        }

    }
    else {
        // compare b and c
        int res = compareAdjs(&b[0], &c[0]);
        if (res == 0) {
            printf("NOT EQ");
        }
        else {
            printf("All good!)\n");
        }

    }


    // if (m % 2 != 0) {
    //     printAdj(&answer_pragma[0]);
    // }
    // else {
    //     printAdj(&b[0]);
    // }

    free(a);
    free(b);
    free(c);
    free(answer_pragma);
    free(answer_without_pragma);

    return 0;
}