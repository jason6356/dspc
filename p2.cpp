//#include "stdafx.h"
#include "omp.h"
#include <stdio.h>

#define NUM_THREADS 1

static long num_steps = 100000;
double step;


int main()
{
    int i,nthread;
    //double x, pi, sum = 0.0;
    double pi, sum[NUM_THREADS];
    omp_set_num_threads(NUM_THREADS);
    double time = omp_get_wtime();
    step = 1.0 / (double)num_steps;
#pragma omp parallel
    {
        int i, id, nth;
        double x;
        id = omp_get_thread_num();
        nth = omp_get_num_threads();
        if (id == 0) nthread = nth;
        for (i = id,sum[id]=0.0; i < num_steps; i+=nth)
        {
            x = (i + 0.5) * step;
            
            sum[id] += 4.0 / (1.0 + x * x);
        }
        
    }
    double end_time = omp_get_wtime();
    for (i = 0, pi = 0.0; i < nthread; i++) {
        pi += sum[i] * step;
    }
   
    printf("%f\n", pi);
    printf("Work took %f seconds\n", end_time - time);
    
    return 0;
}
