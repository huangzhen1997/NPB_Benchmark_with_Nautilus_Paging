#include <stdint.h>

static inline uint64_t __attribute__((always_inline))
rdtscasm (void)
{
    uint32_t lo, hi;
    asm volatile("rdtsc" : "=a"(lo), "=d"(hi));
    return lo | ((uint64_t)(hi) << 32);
}

void rdtsc_(uint64_t* t)
{
    *t = rdtscasm();
}
