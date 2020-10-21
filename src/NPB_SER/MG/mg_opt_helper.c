#include <nautilus/libccompat.h>

void write_1000()
{
    printf("\n NAS Parallel Benchmarks (NPB3.3-SER) - MG Benchmark\n");
}

void write_51()
{
    printf("No input file. Using compiled defaults\n");
}

void write_1001(int* nx, int* ny, int* nz, char* class)
{
    printf(" Size: %d x %d x %d (class %c)\n", *nx, *ny, *nz, *class);
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
    printf("   iter %d\n", *it);
}

void write_100()
{
    printf("\n Benchmark completed \n");
}

void write_200(double* rnm2, double* err)
{
    printf(" VERIFICATION SUCCESSFUL\n L2 Norm is %20.13e \nError is %20.13e\n", *rnm2, *err);
}
void write_300(double* rnm2, double* verify_value)
{
    printf(" VERIFICATION FAILED \nL2 Norm is %20.13e \nThe correct L2 Norm is %20.13e\n",*rnm2, *verify_value);
}

void write_400()
{
    printf(" Problem size unknown No VERIFICATION PERFORMED\n");
}

void write_201(double* l2)
{
    printf(" L2 Norm is %f\n", *l2);
}

void write_001()
{
    printf(" in setup, ");
}

void write_002()
{
    printf(" k  lt  nx  ny  nz  n1  n2  n3 is1 is2 is3 ie1 ie2 ie3");
}

void write_9(int* k, int* lt, int* ng1, int* ng2, int* ng3, int* n1, int* n2, int* n3,
             int* is1, int* is2, int* is3, int* ie1, int* ie2, int* ie3)
{
    printf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d",*k,*lt,*ng1,*ng2,*ng3,*n1,*n2,*n3,*is1,
                                                       *is2,*is3,*ie1,*ie2,*ie3);
}

void write_7(int* kk, char* title, double* rnm2, double* rnmu)
{
    char buf[9];
    buf[8] = '\0';
    for(int i = 0;i < 8;i++){
        buf[i] = title[i];
    }
    printf(" Level %d in %s: norms = %21.14f, %21.14f\n", *kk, buf, *rnm2, *rnmu);
}

void write_debug_1(double* rnm2, double* verify_value, double* err)
{
    printf("rnm2 = %16.14f, verify_value = %16.14f, err = %16.14f\n",*rnm2, *verify_value, *err);
}

void write_debug_2(double*s, double* dn, double* rnm2,int* n1, int* n2, int* n3)
{
    printf("debug norm2u3 --> s = %20.13e, dn = %20.13e, rnm2 = %20.13e n1 = %d, n2 = %d, n3 = %d\n", *s, *dn, *rnm2,*n1, *n2,*n3);
}

void write_debug_3(double* r)
{
    printf("r**2 = %20.13e\n", *r);
}

void write_debug_4(double* v)
{
    printf("u(i1,i2,i3) = %20.13e\n", *v);
}
