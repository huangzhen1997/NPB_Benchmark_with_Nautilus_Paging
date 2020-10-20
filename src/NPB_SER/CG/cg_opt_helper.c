#include <nautilus/libccompat.h>

void write_1000()
{
    printf("\n\n NAS Parallel Benchmarks (NPB3.3-SER) - CG Benchmark\n");
}

void write_1001(int* na)
{
    printf(" Size: %d\n", *na);
}

void write_1002(int* niter)
{
    printf(" Iterations: %d\n\n", *niter);
}

void write_2000(unsigned long* tm)
{
    printf(" Initialization time = %lu cycles\n", *tm);
}

void write_9000()
{
    printf("\n   iteration           ||r||                 zeta\n");
}

void write_9001(int* it, double* rnorm, double* zeta)
{
    printf("    %d       %20.14e %20.13f\n", *it, *rnorm, *zeta);
}

void write_100()
{
    printf(" Benchmark completed \n");
}

void write_200()
{
    printf(" VERIFICATION SUCCESSFUL \n");
}

void write_201(double* zeta)
{
    printf(" Zeta is    %20.13e\n", *zeta);
}

void write_202(double* err)
{
    printf(" Error is   %20.13e\n", *err);
}

void write_300()
{
    printf(" VERIFICATION FAILED\n");
}

void write_301(double* zeta)
{
    printf(" Zeta                %20.13e\n", *zeta);
}

void write_302(double* zeta_verify_value)
{
    printf(" The correct zeta is %20.13e\n", *zeta_verify_value);
}

void write_400()
{
    printf(" Problem size unknown\n");
}

void write_401()
{
    printf(" NO VERIFICATION PERFORMED\n");
}

void write_sparse_1()
{
    printf("Space for matrix elements exceeded in sparse\n");
}

void write_sparse_2(int* nza, int* nz)
{
    printf("nza, nzmax = %d %d\n", *nza, *nz);
}

void write_sparse_3(int* i)
{
    printf("internal error in sparse: i= %d\n", *i);
}

void write_debug_001(double* norm_temp2)
{
    printf("Debug conj_grad: norm_temp2 = %20.13e\n", *norm_temp2);
}

void write_debug_002(double* z, double* alpha, double* p)
{
    printf("%20.13e %20.13e %20.13e\n", *z, *alpha, *p);
}

void write_debug_003(double* z, int*j)
{
    printf("z(%d) = %20.13e\n",*j, *z);
}

void write_debug_004(double* ratio)
{
    printf("ratio = %20.13e\n", *ratio);
}
