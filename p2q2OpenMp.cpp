//#include "stdafx.h"
#include "omp.h"
#include <stdio.h>
#define PADS 8
#define NUM_THREADS 1

static long num_steps = 100000;
double step;


int main()
{
    //double x, pi, sum = 0.0;
    double pi, sum;
    omp_set_num_threads(NUM_THREADS);
    double time = omp_get_wtime();
    step = 1.0 / (double)num_steps;

#pragma omp reduction(+:sum)
    //tells the compiler to perform a reduction operation on the variable sum
    {
        int i, id, nth;
        double x;
        id = omp_get_thread_num();
        nth = omp_get_num_threads();
        for (i = id, sum = 0.0; i < num_steps; i += nth)
        {
            x = (i + 0.5) * step;

            sum+= 4.0 / (1.0 + x * x);
            printf("Thread_ID = %d\n Sum = %f\n", id, sum);
        }
    }
    double end_time = omp_get_wtime();
    pi = sum * step;
    printf("%f\n", pi);
    printf("Work took %f seconds\n", end_time - time);

    return 0;
}
