#include "wtime.h"
#include <stdlib.h>
#include <stdint.h>

/*  Prototype  */
void wtime( double * );
static inline uint64_t __attribute__((always_inline))
rdtsc (void)
{
    uint32_t lo, hi;
    asm volatile("rdtsc" : "=a"(lo), "=d"(hi));
    return lo | ((uint64_t)(hi) << 32);
}



/*****************************************************************/
/******         E  L  A  P  S  E  D  _  T  I  M  E          ******/
/*****************************************************************/
uint64_t elapsed_time( void )
{
    uint64_t t;

//    wtime( &t );
    t = rdtsc();
    return( t );
}


uint64_t start[64], elapsed[64];

/*****************************************************************/
/******            T  I  M  E  R  _  C  L  E  A  R          ******/
/*****************************************************************/
void timer_clear( int n )
{
    elapsed[n] = 0.0;
}


/*****************************************************************/
/******            T  I  M  E  R  _  S  T  A  R  T          ******/
/*****************************************************************/
void timer_start( int n )
{
    start[n] = elapsed_time();
}


/*****************************************************************/
/******            T  I  M  E  R  _  S  T  O  P             ******/
/*****************************************************************/
void timer_stop( int n )
{
    uint64_t t, now;

    now = elapsed_time();
    t = now - start[n];
    elapsed[n] += t;

}


/*****************************************************************/
/******            T  I  M  E  R  _  R  E  A  D             ******/
/*****************************************************************/
uint64_t timer_read( int n )
{
    return( elapsed[n] );
}

