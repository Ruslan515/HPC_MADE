// метод Монте-Карло для оценки числа pi

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

const size_t N = 1<<26;

int main (int argc, char *argv[])
{	
	double x, y;
    double pi, start, end;
	int i, tid, circle_cnt = 0;

	start = omp_get_wtime();
	#pragma omp parallel private(i,x,y,tid)
	{
		tid = omp_get_thread_num();
		unsigned int seed = 15 * tid;
		#pragma omp for reduction(+:circle_cnt)
		for (i = 0; i < N; i++) 
		{
			x = (double)rand_r(&seed)/(double)(RAND_MAX);
			y = (double)rand_r(&seed)/(double)(RAND_MAX);

			if ((x*x + y*y) <= 1)
				circle_cnt++;
		}
	}
	end = omp_get_wtime();
	pi = (double)(4 * circle_cnt) / N;

    printf(
		"\tКоличество нитей == %d\n\tКоличество шагов == %d\n\tВремя(сек) == %d\n",
		omp_get_max_threads(), N, (end-start)
	);

    printf("\tPi == %f\n", pi);
	return 0;
}