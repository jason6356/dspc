//#include "stdafx.h"
#include "omp.h"
#include <stdio.h>
#define PADS 8
#define NUM_THREADS 16

static long num_steps = 100000;
double step;


int main()
{
    //double x, pi, sum = 0.0;
    double pi, sum = 0.0;
    omp_set_num_threads(NUM_THREADS);
    double time = omp_get_wtime();
    step = 1.0 / (double)num_steps;

    //tells the compiler to perform a reduction operation on the variable sum
#pragma omp parallel reduction(+ : sum)
    {
        int i, id, nth;
        double x;
        id = omp_get_thread_num();
        nth = omp_get_num_threads();
        for (i = id, sum = 0.0; i < num_steps; i += nth)
        {
            x = (i + 0.5) * step;

            sum += 4.0 / (1.0 + x * x);
        }
        //printf("ID = %d\nSum = %f\n", id,sum);
    }
    double end_time = omp_get_wtime();
    pi = sum * step;
    printf("%lf\n", sum);
    printf("%lf\n", pi);
    printf("Work took %f seconds\n", end_time - time);


    return 0;
}
