/*****************************************************************/
/****** wrapper for  C  _  P  R  I  N  T  _  R  E  S  U  L  T  S */
/*****************************************************************/
#include <nautilus/libccompat.h>

void w_c_print_results( char*   class,
                      int*    n1, 
                      int*    n2,
                      int*    n3,
                      int*    niter,
                      unsigned long* t,
                      double* mops,
                      int*    passed_verification
                      )
{

    printf( " Class           =                        %c\n", *class );

    if(*n3 == 0 ) {
        unsigned long nn = 1;
        int n1_cpy = *n1;
        while(n1_cpy-- > 0) nn *= 2;
        printf( " Size            =             %12ld\n", nn );   /* as in IS */
    }
    else
        printf( " Size            =             %4dx%4dx%4d\n", *n1,*n2,*n3 );

    printf( " Iterations      =             %12d\n", *niter );
 
    printf( " Time in cycles =             %lu\n", *t );

    printf( " Mop/s total     =             %12.2f\n", *mops );


    if( passed_verification < 0 )
        printf( " Verification    =            NOT PERFORMED\n" );
    else if( passed_verification )
        printf( " Verification    =               SUCCESSFUL\n" );
    else
        printf( " Verification    =             UNSUCCESSFUL\n" );

}
 
