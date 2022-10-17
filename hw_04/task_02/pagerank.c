#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


void dot_mat_vec(double *adj_matrix, double *V, double *C, int N) {

	#pragma omp parallel for shared(C, adj_matrix, V, N)
    for (int i = 0; i < N; ++i) {
        C[i] = 0;
        for (int j = 0; j < N; ++j)
        	C[i] += adj_matrix[i * N + j] * V[j];
    }
}

double dist_L1(double *A, double *B, int N) {
	double dist = 0;
	#pragma omp parallel for shared(A, B, N) reduction(+:dist)
    for (int i = 0; i < N; ++i)
        dist += fabs(A[i] - B[i]);

    return dist;
}


void PageRank(double *adj_matrix, double *res, int N) {
	double eps = 1e-6;
    double damping = 0.85;
    int maxIter = 1e6;
    double *adj_matrix_norm = (double *) malloc(N * N * sizeof(double));
	double colSum;
	int i, j;

	#pragma omp parallel for shared(adj_matrix, adj_matrix_norm, N)
    for (i = 0; i < N; i++) {
    	colSum = 0;
    	for (j = 0; j < N; j++) {
    		colSum += adj_matrix[j * N + i];
    	}    	
    	for (j = 0; j < N; j++) {
    		if (colSum != 0)
    			adj_matrix_norm[j * N + i] = adj_matrix[j * N + i] / colSum;
    		else 
    			adj_matrix_norm[j * N + i] = 0;
    	}
    }

    double *vector = (double *) malloc(N * sizeof(double));
    #pragma omp parallel for shared(vector, N)
    for (i = 0; i < N; ++i) {
    	vector[i] = 1.0 / N;
    }

    for (i = 0; i < maxIter; ++i) {
    	dot_mat_vec(adj_matrix_norm, vector, res, N);
    	for (j = 0; j < N; ++j) {
    		res[j] = ((1 - damping) / N) + (damping * res[j]);
    	}

    	if (dist_L1(vector, res, N) < eps)
    		break;

    	memcpy(vector, res, N * sizeof(double));
    }
    free(adj_matrix_norm);
    free(vector);
}


int main() {
	FILE *fp = fopen("adj_graph.txt", "r");
	int num;
	int N = 8;
	double *adj_matrix = (double *) malloc(N * N * sizeof(double));
    double *res = (double *) malloc(N * sizeof(double));

    int i = 0;
    while(fscanf(fp, "%d", &num) != EOF ) {
    	adj_matrix[i] = num;
        i++;
    }
    fclose(fp);

    PageRank(adj_matrix, res, N);

    double sum = 0;
    
    printf("Page rank:\n");

    for (i = 0; i < N; ++i)
    {
        printf("%d: %f\n", i, res[i]);
        sum += res[i];
    }
    printf("\nsum: %f\n", sum);

    free(adj_matrix);
    free(res);

    return 0;
}