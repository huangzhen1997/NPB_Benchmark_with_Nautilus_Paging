#include <nautilus/libccompat.h>


void write_sp_1000()
{
    printf(" NAS Parallel Benchmarks (NPB3.3-SER) - SP Benchmark\n");
}

void write_sp_234()
{
    printf(" No input file inputsp.data. Using compiled defaults\n");
}

void write_sp_1001(int* a, int* b, int* c)
{
    printf(" Size: %4d %4d %4d\n", *a, *b, *c);
}

void write_sp_1002(int* niter, double* dt)
{
    printf(" Iterations: %4d     dt: %10.6f\n", *niter, *dt);
}

void write_sp_200(int* step)
{
    printf(" Time step %4d\n", *step);
}

void write_verify_1990(char* a)
{
    printf(" Verification being performed for class %c\n", *a);
}

void write_verify_2000(double* epsilon)
{
    printf(" accuracy setting for epsilon = %20.13e\n", *epsilon);
}

void write_verify_1000(double* dtref)
{
    printf(" accuracy setting for epsilon = %15.8e\n", *dtref);
}

void write_verify_1995()
{
    printf(" Unknown class\n");
}

void write_verify_2001()
{
    printf(" Comparison of RMS-norms of residual\n");
}

void write_verify_2005()
{
    printf(" RMS-norms of residual\n");
}

void write_verify_2015(int* m, double* xce)
{
    printf("          %2d %20.13e\n", *m, *xce);
}

void write_verify_2011(int*m, double* xcr, double* xcrref, double* xcrdif)
{
    printf("          %2d %20.13e %20.13e %20.13e\n", *m, *xcr, *xcrref, *xcrdif);
}

void write_verify_2010(int* m, double* xcr, double* xcrref, double* xcrdif)
{
    printf(" FAILURE: %2d %20.13e %20.13e %20.13e\n", *m, *xcr, *xcrref, *xcrdif);
}

void write_verify_2002()
{
    printf(" Comparison of RMS-norms of solution error\n");
}

void write_verify_2006()
{
    printf(" RMS-norms of solution error\n");
}

void write_verify_2022()
{
    printf(" No reference values provided\n");
}

void write_verify_2023()
{
    printf(" No verification performed\n");
}

void write_verify_2020()
{
    printf(" Verification Successful\n");
}

void write_verify_2021()
{
    printf(" Verification failed\n");
}

void write_sp_print1(int* a, int* b, int* c)
{
    printf("%d %d %d\n", *a, *b, *c);
}

void write_sp_print2()
{
    printf(" Problem size too big for compiled array sizes\n");
}