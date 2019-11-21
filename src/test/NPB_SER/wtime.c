#include <nautilus/libccompat.h>

void wtime(double *t)
{
  static int sec = -1;
  struct timespec tv;
  //gettimeofday(&tv, (void *)0);
  clock_gettime(CLOCK_MONOTONIC, &tv);
  if (sec < 0) sec = tv.tv_sec;
  *t = (tv.tv_sec - sec) + 1.0e-9*tv.tv_nsec;
}

    
