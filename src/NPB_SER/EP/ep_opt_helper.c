#include <nautilus/libccompat.h>

void write_1000() {
    printf(" \n\nNAS Parallel Benchmarks (NPB3.3-SER) - EP Benchmark\n");
}

void write_1001(double* size){
    printf(" Number of random numbers generated: %f\n", *size);
}

void write_11(unsigned long* tm, int* m,double* gc,double* x, double* y, int* nq, double*q)
{
    printf("EP Benchmark Results:\n\n"
           "CPU cycles = %lu\n"
           "N = 2^%d\n"
           "No. Gaussian Pairs = %15.0f\n"
           "Sums = %20.13e %20.13e\n"
           "Counts:\n",*tm, *m, *gc, *x, *y);
    for(int j = 0;j < *nq;j++)
    {
        printf("%3d %15f\n",j,q[j]);
    }
}
