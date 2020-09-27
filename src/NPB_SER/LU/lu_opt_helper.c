#include <nautilus/libccompat.h>

void write_read_input_1000()
{
    printf("\n\n NAS Parallel Benchmarks (NPB3.3-SER) - LU Benchmark\n\n");
}

void write_ri_2001()
{
    printf("     PROBLEM SIZE IS TOO SMALL - \n     SET EACH OF NX, NY AND NZ AT LEAST EQUAL TO 5\n");
}

void write_ri_2002()
{
    printf("     PROBLEM SIZE IS TOO LARGE - \n"
           "     NX, NY AND NZ SHOULD BE EQUAL TO \n"
           "     ISIZ1, ISIZ2 AND ISIZ3 RESPECTIVELY\n");
}

void write_ri_1001(int* x, int* y, int* z)
{
    printf(" Size: %4dx%4dx%4d\n",*x,*y,*z);
}

void write_ri_1002(int* itmax)
{
    printf(" Iterations: %4d\n", *itmax);
}

void write_ssor_200(int* istep)
{
    printf(" Time step %4d\n", *istep);
}

void write_ssor_1004(int* istep)
{
    printf("\nconvergence was achieved after %4d pseudo-time steps\n", *istep);
}

void write_domain_2001(int* x, int* y, int* z)
{
    printf("     SUBDOMAIN SIZE IS TOO SMALL - \n"
           "     ADJUST PROBLEM SIZE OR NUMBER OF PROCESSORS\n"
           "     SO THAT NX, NY AND NZ ARE GREATER THAN OR EQUAL\n"
           "     TO 4 THEY ARE CURRENTLY %3d %3d %3d\n", *x, *y, *z);
}

void write_domain_2002(int* x, int* y, int* z)
{
    printf("     SUBDOMAIN SIZE IS TOO LARGE - \n"
           "     ADJUST PROBLEM SIZE OR NUMBER OF PROCESSORS\n"
           "     SO THAT NX, NY AND NZ ARE LESS THAN OR EQUAL TO \n"
           "     ISIZ1, ISIZ2 AND ISIZ3 RESPECTIVELY.  THEY ARE\n"
           "     CURRENTLY %4d %4d %4d\n", *x, *y, *z);
}

void write_verify_1990(char* class)
{
    printf("\n Verification being performed for class %c\n", *class);
}

void write_verify_2000(double* epsilon)
{
    printf(" Accuracy setting for epsilon = %20.13e\n", *epsilon);
}

void write_verify_1000(double* dtref)
{
    printf(" DT does not match the reference value of %15.8e\n", *dtref);
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

void write_verify_2015(int* m, double* xcr)
{
    printf("          %2d  %20.13e\n", *m, *xcr);
}

void write_verify_2011(int* m, double* xcr, double* xcrref, double* xcrdif)
{
    printf("          %2d  %20.13e %20.13e %20.13e\n", *m, *xcr, *xcrref, *xcrdif);
}

void write_verify_2010(int* m, double* xcr, double* xcrref, double* xcrdif)
{
    printf(" FAILURE: %2d  %20.13e %20.13e %20.13e\n", *m, *xcr, *xcrref, *xcrdif);
}

void write_verify_2002()
{
    printf(" Comparison of RMS-norms of solution error\n");
}

void write_verify_2006()
{
    printf(" RMS-norms of solution error\n");
}

void write_verify_2025()
{
    printf(" Comparison of surface integral\n");
}

void write_verify_2026()
{
    printf(" Surface integral\n");
}

void write_verify_2030(double* xci)
{
    printf("              %20.13e\n", *xci);
}

void write_verify_2032(double* xci, double* xciref, double* xcidif)
{
    printf("              %20.13e %20.13e %20.13e\n", *xci, *xciref, *xcidif);
}

void write_verify_2031(double* xci, double* xciref, double* xcidif)
{
    printf(" FAILURE:     %20.13e %20.13e %20.13e\n", *xci, *xciref, *xcidif);
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

void write_debug_001(int* i, int* j)
{
    printf("debug: still alive in blts %d   %d\n",*i, *j);
}

void write_debug_002(double* rsdnm, double* errnm, double* frc)
{
    printf("debug   %20.13e %20.13e %20.13e\n", *rsdnm, *errnm, *frc);
}

void write_debug_003(int* i, int* j, int* k, double* v1, double* v2, double* v3, double* v4, double* v5)
{
    printf("----%d  %d  %d----\n"
           "v1 = %20.13e    v2 = %20.13e\n"
           "v3 = %20.13e    v4 = %20.13e\n"
           "v5 = %20.13e\n",*i,*j,*k,*v1,*v2,*v3,*v4,*v5);
}

void write_debug_location(int* j, int* i, int* m)
{
    printf("still alive %d %d %d\n", *j, *i, *m);
}
