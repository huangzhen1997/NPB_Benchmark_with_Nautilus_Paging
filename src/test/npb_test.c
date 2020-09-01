#include <nautilus/nautilus.h>
#include <nautilus/libccompat.h>
#include <test/test.h>


void printdouble()
{
    double a = 3.1415;
    double b = 0.3312;
    printf("%8.4f      %8.4f\n", a, b);
}

void dbpone(int* a, int* b)
{
    printf("inside ep! %d   %d\n", *a, *b);
}

void debugdummy()
{
}

void printvalue(double* a, double* b, double* c, double* d)
{
    printf("%16.14f  -----   %16.14f    ------- %16.14f   ---------   %16.14f\n", *a, *b, *c, *d);
}

extern void npb_ft_entry();

static int
callffunc(int argc, char** argv)
{
    printf("calling ffunc\n");
    npb_ft_entry();
    return 0;
}

static struct nk_test_impl npb_test_impl = {
    .name = "npb_test",
    .handler = callffunc,
    .default_args = "",
};

nk_register_test(npb_test_impl);
