#include <nautilus/libccompat.h>

void write_1000()
{
    printf("\n\n  NAS Parallel Benchmarks (NPB3.3-SER)"
           " - FT Benchmark\n");
}

void write_1001(int* nx, int* ny, int* nz)
{
    printf(" Size                : %dx%dx%d", *nx, *ny, *nz);
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

//void write_30(
