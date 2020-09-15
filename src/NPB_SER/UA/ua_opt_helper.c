#include <nautilus/libccompat.h>

void write_1000()
{
    printf(" NAS Parallel Benchmarks (NPB3.3-SER) - UA Benchmark\n");
}

void write_234()
{
    printf(" No input file inputsp.data. Using compiled defaults\n");
}

void write_1001(int* refine_max)
{
    printf(" Levels of refinement: %d\n", *refine_max);
}

void write_1002(int* fre)
{
    printf(" Adaptation frequency: %d\n", *fre);
}

void write_1003(int* niter, double* dtime)
{
    printf(" Time steps:           %d    dt: %f\n", *niter, *dtime);
}

void write_1004(int* nmxh)
{
    printf(" CG iterations:        %d\n", *nmxh);
}

void write_1005(double* alpha)
{
    printf(" Heat source radius:   %f\n", *alpha);
}

void write_adapt_1000(int* step, int* irefine, int* icoarsen, int* nelt)
{
    printf("Step %d, : elements refined, merged, total: %d %d %d\n", *step, *irefine,
                                                                     *icoarsen, *nelt);
}

void write_verify_1990(char* class)
{
    printf(" Verification being performed for class %c\n", *class);
}

void write_verify_2000(double* epsilon)
{
    printf(" accuracy setting for epsilon = %f\n", *epsilon);
}

void write_verify_1995()
{
    printf("Unkown class\n");
}

void write_verify_2001()
{
    printf(" Comparison of temperature integrals");
}

void write_verify_2005()
{
    printf(" Temperature integral");
}

void write_verify_2015(double* norm)
{
    printf("          %f", *norm);
}

void write_verify_2011(double* norm, double* norm_ref, double* norm_dif)
{
    printf("          %f %f %f", *norm, *norm_ref, *norm_dif);
}

void write_verify_2010(double* norm, double* norm_ref, double* norm_dif)
{
    printf(" FAILURE: %f %f %f", *norm, *norm_ref, *norm_dif);
}

void write_verify_2022()
{
    printf(" No reference values provided");
}

void write_verify_2023()
{
    printf(" No verification performed");
}

void write_verify_2020()
{
    printf(" Verification Successful");
}

void write_verify_2021()
{
    printf(" Verification failed");
}

void write_debug(int* i, int* j, int* k, int* isize)
{
    printf("%d  %d  %d  %d\n", *i, *j, *k, *isize);
}

void write_debug1(double* value)
{
    printf("xrm1_s:%f\n", *value);
}

void write_debug_size_e(int* iel, int* value)
{
    printf("size_e(%d): %d\n", *iel, *value);
}

void write_debug_dlog_xc(double* xc1, double* xc2, double* value)
{
    printf("xc1: %9.4f         xc2:%9.4f          dlog:%9.4f\n",*xc1, *xc2, *value);
}
