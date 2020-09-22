#include <nautilus/libccompat.h>

void write_1000()
{
    printf("\n\n  NAS Parallel Benchmarks (NPB3.3-SER)"
           " - FT Benchmark\n");
}

void write_1001(int* nx, int* ny, int* nz)
{
    printf(" Size                : %dx%dx%d\n", *nx, *ny, *nz);
}

void write_1002(int* niter)
{
    printf(" Iterations          :    %10d\n", *niter);
}

void write_40(char* msg, int* tm)
{
    char buf[27];
    for(int i = 0;i < 26;i++)
        buf[i] = msg[i];
    buf[26] = '\0';
    printf("%s = %d\n", buf, *tm);
}

void write_120(char* msg, int* len)
{
    char buf[14];
    for(int i = 0;i < *len;i++)
        buf[i] = msg[i];
    buf[*len] = '\0';
    printf(" Verification test for FT %s\n", buf);
}

void write_appft_83()
{
    printf("FT subroutine timers\n");
}

void write_debug_1(double* err, int* nt)
{
    printf("err = %20.13e   %d\n", *err, *nt);
}

void write_debug_2(double* a)
{
    printf("a = %20.13e\n", *a);
}

void write_debug_3(int*ii, int* ji,int* ki,double*r, double*i)
{
    printf("u(%d,%d,%d) = %20.13e + %20.13ei\n",*ii,*ji,*ki,*r,*i);
}

void write_debug_4(double* twiddle)
{
    printf("twiddle = %20.13e\n", *twiddle);
}

void write_debug_5(double* r, double* i)
{
    printf("y = %20.13E,%20.13E\n", *r, *i);
}

void write_debug_6(int* x, int* y, int* z)
{
    printf("x = %d  y = %d  z = %d\n", *x,*y,*z);
}

void write_debug_7(double* r1,double* i1)
{
    printf("dconjg:%20.13e  %20.13e\n", *r1, *i1);
}

void write_debug_8(double* ti, double* buf1, double* buf2)
{
    printf("%20.13e %20.13e %20.13e\n",*ti, *buf1, *buf2);
}
