#include <nautilus/naut_types.h>
void rdtsc (uint64_t* t)
{
    uint32_t lo, hi;
    asm volatile("rdtsc" : "=a"(lo), "=d"(hi));
    *t =  lo | ((uint64_t)(hi) << 32);
}

