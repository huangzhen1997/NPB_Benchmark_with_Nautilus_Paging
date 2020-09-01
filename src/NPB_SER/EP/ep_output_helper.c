#include <nautilus/libccompat.h>

void write_1000() {
    printf(" \n\nNAS Parallel Benchmarks (NPB3.3-SER) - EP Benchmark\n");
}

void write_1001(int* m){
    unsigned long size = 2;
    int m_buf = *m;
    while(m_buf > 0) {
        m_buf = m_buf - 1;
        size = size * 2;
    }
    printf("m = %d\n", *m);
    printf(" Number of random numbers generated: %lu\n", size);
}
