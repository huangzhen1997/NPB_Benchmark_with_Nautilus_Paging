#include <nautilus/libccompat.h>

void write_1000()
{
    printf("\n NAS Parallel Benchmarks (NPB3.3-SER) - MG Benchmark\n");
}

void write_51()
{
    printf("No input file. Using compiled defaults");
}

void write_1001(int* nx, int* ny, int* nz, char* class)
{
    printf(" Size: %d x %d x %d (class %c)", *nx, *ny, *nz, *class);
}

void write_1002(int* nit)
{
    printf(" Iterations: %d\n", *nit);
}

void write_inittime(unsigned long* tinit)
{
    printf(" Initialization time : %lu cycles\n", *tinit);
}

void write_80(int* it)
{
    printf("   iter %d", *it);
}

void write_100()
{
    printf("\n Benchmark completed ");
}

void write_200(double* rnm2, double* err)
{
    printf(" VERIFICATION SUCCESSFUL L2 Norm is %20.13f Error is %20.13f", *rnm2, *err);
}
void write_300(double* rnm2, double* err)
{
    printf(" VERIFICATION FAILED L2 Norm is %20.13f The correct L2 Norm is %20.13f", *rnm2, *err);
}

void write_400()
{
    printf(" Problem size unknown No VERIFICATION PERFORMED");
}

void write_201(double* l2)
{
    printf(" L2 Norm is %f", *l2);
}
