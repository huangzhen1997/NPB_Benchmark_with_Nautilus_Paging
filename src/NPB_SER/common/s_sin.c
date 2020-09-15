
/* @(#)s_sin.c 1.3 95/01/18 */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * ====================================================
 */

/* sin(x)
 * Return sine function of x.
 *
 * kernel function:
 *	__kernel_sin		... sine function on [-pi/4,pi/4]
 *	__kernel_cos		... cose function on [-pi/4,pi/4]
 *	__ieee754_rem_pio2	... argument reduction routine
 *
 * Method.
 *      Let S,C and T denote the sin, cos and tan respectively on 
 *	[-PI/4, +PI/4]. Reduce the argument x to y1+y2 = x-k*pi/2 
 *	in [-pi/4 , +pi/4], and let n = k mod 4.
 *	We have
 *
 *          n        sin(x)      cos(x)        tan(x)
 *     ----------------------------------------------------------
 *	    0	       S	   C		 T
 *	    1	       C	  -S		-1/T
 *	    2	      -S	  -C		 T
 *	    3	      -C	   S		-1/T
 *     ----------------------------------------------------------
 *
 * Special cases:
 *      Let trig be any of sin, cos, or tan.
 *      trig(+-INF)  is NaN, with signals;
 *      trig(NaN)    is that NaN;
 *
 * Accuracy:
 *	TRIG(x) returns trig(x) nearly rounded 
 */

#include "fdlibm.h"

static const double
two54   =  1.80143985094819840000e+16, /* 0x43500000, 0x00000000 */
        twom54  =  5.55111512312578270212e-17, /* 0x3C900000, 0x00000000 */
        huge   = 1.0e+300,
        tiny   = 1.0e-300;


double fabs(double x)
{
    __HI(x) &= 0x7fffffff;
    return x;
}

double floor(double x)
{
    int i0,i1,j0;
    unsigned i,j;
    i0 =  __HI(x);
    i1 =  __LO(x);
    j0 = ((i0>>20)&0x7ff)-0x3ff;
    if(j0<20) {
        if(j0<0) {  /* raise inexact if x != 0 */
            if(huge+x>0.0) {/* return 0*sign(x) if |x|<1 */
                if(i0>=0) {i0=i1=0;} 
                else if(((i0&0x7fffffff)|i1)!=0)
                { i0=0xbff00000;i1=0;}
            }
        } else {
            i = (0x000fffff)>>j0;
            if(((i0&i)|i1)==0) return x; /* x is integral */
            if(huge+x>0.0) {    /* raise inexact flag */
                if(i0<0) i0 += (0x00100000)>>j0;
                i0 &= (~i); i1=0;
            }
        }
    } else if (j0>51) {
        if(j0==0x400) return x+x;   /* inf or NaN */
        else return x;      /* x is integral */
    } else {
        i = ((unsigned)(0xffffffff))>>(j0-20);
        if((i1&i)==0) return x; /* x is integral */
        if(huge+x>0.0) {        /* raise inexact flag */
            if(i0<0) {
                if(j0==20) i0+=1; 
                else {
                    j = i1+(1<<(52-j0));
                    if(j<i1) i0 +=1 ;   /* got a carry */
                    i1=j;
                }
            }
            i1 &= (~i);
        }
    }
    __HI(x) = i0;
    __LO(x) = i1;
    return x;
}




double copysign(double x, double y)
{
    __HI(x) = (__HI(x)&0x7fffffff)|(__HI(y)&0x80000000);
    return x;
}



double scalbn (double x, int n)
{
    int  k,hx,lx;
    hx = __HI(x);
    lx = __LO(x);
    k = (hx&0x7ff00000)>>20;        /* extract exponent */
    if (k==0) {             /* 0 or subnormal x */
        if ((lx|(hx&0x7fffffff))==0) return x; /* +-0 */
        x *= two54; 
        hx = __HI(x);
        k = ((hx&0x7ff00000)>>20) - 54; 
        if (n< -50000) return tiny*x;   /*underflow*/
    }
    if (k==0x7ff) return x+x;       /* NaN or Inf */
    k = k+n; 
    if (k >  0x7fe) return huge*copysign(huge,x); /* overflow  */
    if (k > 0)              /* normal result */
    {__HI(x) = (hx&0x800fffff)|(k<<20); return x;}
    if (k <= -54)
        if (n > 50000)  /* in case integer overflow in n+k */
            return huge*copysign(huge,x);   /*overflow*/
        else return tiny*copysign(tiny,x);  /*underflow*/
    k += 54;                /* subnormal result */
    __HI(x) = (hx&0x800fffff)|(k<<20);
    return x*twom54;
}


static const int init_jk[] = {2,3,4,6}; /* initial value for jk */

static const double PIo2[] = {
    1.57079625129699707031e+00, /* 0x3FF921FB, 0x40000000 */
    7.54978941586159635335e-08, /* 0x3E74442D, 0x00000000 */
    5.39030252995776476554e-15, /* 0x3CF84698, 0x80000000 */
    3.28200341580791294123e-22, /* 0x3B78CC51, 0x60000000 */
    1.27065575308067607349e-29, /* 0x39F01B83, 0x80000000 */
    1.22933308981111328932e-36, /* 0x387A2520, 0x40000000 */
    2.73370053816464559624e-44, /* 0x36E38222, 0x80000000 */
    2.16741683877804819444e-51, /* 0x3569F31D, 0x00000000 */
};

static const double         
zero =  0.00000000000000000000e+00, /* 0x00000000, 0x00000000 */
     one =  1.00000000000000000000e+00, /* 0x3FF00000, 0x00000000 */
     two24 =  1.67772160000000000000e+07, /* 0x41700000, 0x00000000 */
     twon24  =  5.96046447753906250000e-08; /* 0x3E700000, 0x00000000 */

int __kernel_rem_pio2(double *x, double *y, int e0, int nx, int prec, const int *ipio2) 
{
    int jz,jx,jv,jp,jk,carry,n,iq[20],i,j,k,m,q0,ih;
    double z,fw,f[20],fq[20],q[20];

    /* initialize jk*/
    jk = init_jk[prec];
    jp = jk;

    /* determine jx,jv,q0, note that 3>q0 */
    jx =  nx-1;
    jv = (e0-3)/24; if(jv<0) jv=0;
    q0 =  e0-24*(jv+1);

    /* set up f[0] to f[jx+jk] where f[jx+jk] = ipio2[jv+jk] */
    j = jv-jx; m = jx+jk;
    for(i=0;i<=m;i++,j++) f[i] = (j<0)? zero : (double) ipio2[j];

    /* compute q[0],q[1],...q[jk] */
    for (i=0;i<=jk;i++) {
        for(j=0,fw=0.0;j<=jx;j++) fw += x[j]*f[jx+i-j]; q[i] = fw;
    }

    jz = jk;
recompute:
    /* distill q[] into iq[] reversingly */
    for(i=0,j=jz,z=q[jz];j>0;i++,j--) {
        fw    =  (double)((int)(twon24* z));
        iq[i] =  (int)(z-two24*fw);
        z     =  q[j-1]+fw;
    }

    /* compute n */
    z  = scalbn(z,q0);      /* actual value of z */
    z -= 8.0*floor(z*0.125);        /* trim off integer >= 8 */
    n  = (int) z;
    z -= (double)n;
    ih = 0;
    if(q0>0) {  /* need iq[jz-1] to determine n */
        i  = (iq[jz-1]>>(24-q0)); n += i;
        iq[jz-1] -= i<<(24-q0);
        ih = iq[jz-1]>>(23-q0);
    } 
    else if(q0==0) ih = iq[jz-1]>>23;
    else if(z>=0.5) ih=2;

    if(ih>0) {  /* q > 0.5 */
        n += 1; carry = 0;
        for(i=0;i<jz ;i++) {    /* compute 1-q */
            j = iq[i];
            if(carry==0) {
                if(j!=0) {
                    carry = 1; iq[i] = 0x1000000- j;
                }
            } else  iq[i] = 0xffffff - j;
        }
        if(q0>0) {      /* rare case: chance is 1 in 12 */
            switch(q0) {
                case 1:
                    iq[jz-1] &= 0x7fffff; break;
                case 2:
                    iq[jz-1] &= 0x3fffff; break;
            }
        }
        if(ih==2) {
            z = one - z;
            if(carry!=0) z -= scalbn(one,q0);
        }
    }

    /* check if recomputation is needed */
    if(z==zero) {
        j = 0;
        for (i=jz-1;i>=jk;i--) j |= iq[i];
        if(j==0) { /* need recomputation */
            for(k=1;iq[jk-k]==0;k++);   /* k = no. of terms needed */

            for(i=jz+1;i<=jz+k;i++) {   /* add q[jz+1] to q[jz+k] */
                f[jx+i] = (double) ipio2[jv+i];
                for(j=0,fw=0.0;j<=jx;j++) fw += x[j]*f[jx+i-j];
                q[i] = fw;
            }
            jz += k;
            goto recompute;
        }
    }

    /* chop off zero terms */
    if(z==0.0) {
        jz -= 1; q0 -= 24;
        while(iq[jz]==0) { jz--; q0-=24;}
    } else { /* break z into 24-bit if necessary */
        z = scalbn(z,-q0);
        if(z>=two24) { 
            fw = (double)((int)(twon24*z));
            iq[jz] = (int)(z-two24*fw);
            jz += 1; q0 += 24;
            iq[jz] = (int) fw;
        } else iq[jz] = (int) z ;
    }

    /* convert integer "bit" chunk to floating-point value */
    fw = scalbn(one,q0);
    for(i=jz;i>=0;i--) {
        q[i] = fw*(double)iq[i]; fw*=twon24;
    }

    /* compute PIo2[0,...,jp]*q[jz,...,0] */
    for(i=jz;i>=0;i--) {
        for(fw=0.0,k=0;k<=jp&&k<=jz-i;k++) fw += PIo2[k]*q[i+k];
        fq[jz-i] = fw;
    }

    /* compress fq[] into y[] */
    switch(prec) {
        case 0:
            fw = 0.0;
            for (i=jz;i>=0;i--) fw += fq[i];
            y[0] = (ih==0)? fw: -fw; 
            break;
        case 1:
        case 2:
            fw = 0.0;
            for (i=jz;i>=0;i--) fw += fq[i]; 
            y[0] = (ih==0)? fw: -fw; 
            fw = fq[0]-fw;
            for (i=1;i<=jz;i++) fw += fq[i];
            y[1] = (ih==0)? fw: -fw; 
            break;
        case 3: /* painful */
            for (i=jz;i>0;i--) {
                fw      = fq[i-1]+fq[i]; 
                fq[i]  += fq[i-1]-fw;
                fq[i-1] = fw;
            }
            for (i=jz;i>1;i--) {
                fw      = fq[i-1]+fq[i]; 
                fq[i]  += fq[i-1]-fw;
                fq[i-1] = fw;
            }
            for (fw=0.0,i=jz;i>=2;i--) fw += fq[i]; 
            if(ih==0) {
                y[0] =  fq[0]; y[1] =  fq[1]; y[2] =  fw;
            } else {
                y[0] = -fq[0]; y[1] = -fq[1]; y[2] = -fw;
            }
    }
    return n&7;
}



double __ieee754_sqrt(double x)
{
    double z;
    int     sign = (int)0x80000000; 
    unsigned r,t1,s1,ix1,q1;
    int ix0,s0,q,m,t,i;

    ix0 = __HI(x);          /* high word of x */
    ix1 = __LO(x);      /* low word of x */

    /* take care of Inf and NaN */
    if((ix0&0x7ff00000)==0x7ff00000) {          
        return x*x+x;       /* sqrt(NaN)=NaN, sqrt(+inf)=+inf
                               sqrt(-inf)=sNaN */
    } 
    /* take care of zero */
    if(ix0<=0) {
        if(((ix0&(~sign))|ix1)==0) return x;/* sqrt(+-0) = +-0 */
        else if(ix0<0)
            return (x-x)/(x-x);     /* sqrt(-ve) = sNaN */
    }
    /* normalize x */
    m = (ix0>>20);
    if(m==0) {              /* subnormal x */
        while(ix0==0) {
            m -= 21;
            ix0 |= (ix1>>11); ix1 <<= 21;
        }
        for(i=0;(ix0&0x00100000)==0;i++) ix0<<=1;
        m -= i-1;
        ix0 |= (ix1>>(32-i));
        ix1 <<= i;
    }
    m -= 1023;  /* unbias exponent */
    ix0 = (ix0&0x000fffff)|0x00100000;
    if(m&1){    /* odd m, double x to make it even */
        ix0 += ix0 + ((ix1&sign)>>31);
        ix1 += ix1;
    }
    m >>= 1;    /* m = [m/2] */

    /* generate sqrt(x) bit by bit */
    ix0 += ix0 + ((ix1&sign)>>31);
    ix1 += ix1;
    q = q1 = s0 = s1 = 0;   /* [q,q1] = sqrt(x) */
    r = 0x00200000;     /* r = moving bit from right to left */

    while(r!=0) {
        t = s0+r; 
        if(t<=ix0) { 
            s0   = t+r; 
            ix0 -= t; 
            q   += r; 
        } 
        ix0 += ix0 + ((ix1&sign)>>31);
        ix1 += ix1;
        r>>=1;
    }

    r = sign;
    while(r!=0) {
        t1 = s1+r; 
        t  = s0;
        if((t<ix0)||((t==ix0)&&(t1<=ix1))) { 
            s1  = t1+r;
            if(((t1&sign)==sign)&&(s1&sign)==0) s0 += 1;
            ix0 -= t;
            if (ix1 < t1) ix0 -= 1;
            ix1 -= t1;
            q1  += r;
        }
        ix0 += ix0 + ((ix1&sign)>>31);
        ix1 += ix1;
        r>>=1;
    }

    /* use floating add to find out rounding direction */
    if((ix0|ix1)!=0) {
        z = one-tiny; /* trigger inexact flag */
        if (z>=one) {
            z = one+tiny;
            if (q1==(unsigned)0xffffffff) { q1=0; q += 1;}
            else if (z>one) {
                if (q1==(unsigned)0xfffffffe) q+=1;
                q1+=2; 
            } else
                q1 += (q1&1);
        }
    }
    ix0 = (q>>1)+0x3fe00000;
    ix1 =  q1>>1;
    if ((q&1)==1) ix1 |= sign;
    ix0 += (m <<20);
    __HI(z) = ix0;
    __LO(z) = ix1;
    return z;
}

double sqrt(double x)
{
    return __ieee754_sqrt(x);
}







static const int two_over_pi[] = {
    0xA2F983, 0x6E4E44, 0x1529FC, 0x2757D1, 0xF534DD, 0xC0DB62, 
    0x95993C, 0x439041, 0xFE5163, 0xABDEBB, 0xC561B7, 0x246E3A, 
    0x424DD2, 0xE00649, 0x2EEA09, 0xD1921C, 0xFE1DEB, 0x1CB129, 
    0xA73EE8, 0x8235F5, 0x2EBB44, 0x84E99C, 0x7026B4, 0x5F7E41, 
    0x3991D6, 0x398353, 0x39F49C, 0x845F8B, 0xBDF928, 0x3B1FF8, 
    0x97FFDE, 0x05980F, 0xEF2F11, 0x8B5A0A, 0x6D1F6D, 0x367ECF, 
    0x27CB09, 0xB74F46, 0x3F669E, 0x5FEA2D, 0x7527BA, 0xC7EBE5, 
    0xF17B3D, 0x0739F7, 0x8A5292, 0xEA6BFB, 0x5FB11F, 0x8D5D08, 
    0x560330, 0x46FC7B, 0x6BABF0, 0xCFBC20, 0x9AF436, 0x1DA9E3, 
    0x91615E, 0xE61B08, 0x659985, 0x5F14A0, 0x68408D, 0xFFD880, 
    0x4D7327, 0x310606, 0x1556CA, 0x73A8C9, 0x60E27B, 0xC08C6B, 
};

static const int npio2_hw[] = {
    0x3FF921FB, 0x400921FB, 0x4012D97C, 0x401921FB, 0x401F6A7A, 0x4022D97C,
    0x4025FDBB, 0x402921FB, 0x402C463A, 0x402F6A7A, 0x4031475C, 0x4032D97C,
    0x40346B9C, 0x4035FDBB, 0x40378FDB, 0x403921FB, 0x403AB41B, 0x403C463A,
    0x403DD85A, 0x403F6A7A, 0x40407E4C, 0x4041475C, 0x4042106C, 0x4042D97C,
    0x4043A28C, 0x40446B9C, 0x404534AC, 0x4045FDBB, 0x4046C6CB, 0x40478FDB,
    0x404858EB, 0x404921FB,
};

/*
 * invpio2:  53 bits of 2/pi
 * pio2_1:   first  33 bit of pi/2
 * pio2_1t:  pi/2 - pio2_1
 * pio2_2:   second 33 bit of pi/2
 * pio2_2t:  pi/2 - (pio2_1+pio2_2)
 * pio2_3:   third  33 bit of pi/2
 * pio2_3t:  pi/2 - (pio2_1+pio2_2+pio2_3)
 */

static const double 
half =  5.00000000000000000000e-01, /* 0x3FE00000, 0x00000000 */
     invpio2 =  6.36619772367581382433e-01, /* 0x3FE45F30, 0x6DC9C883 */
     pio2_1  =  1.57079632673412561417e+00, /* 0x3FF921FB, 0x54400000 */
     pio2_1t =  6.07710050650619224932e-11, /* 0x3DD0B461, 0x1A626331 */
     pio2_2  =  6.07710050630396597660e-11, /* 0x3DD0B461, 0x1A600000 */
     pio2_2t =  2.02226624879595063154e-21, /* 0x3BA3198A, 0x2E037073 */
     pio2_3  =  2.02226624871116645580e-21, /* 0x3BA3198A, 0x2E000000 */
     pio2_3t =  8.47842766036889956997e-32; /* 0x397B839A, 0x252049C1 */

int __ieee754_rem_pio2(double x, double *y)
{
    double z,w,t,r,fn;
    double tx[3];
    int e0,i,j,nx,n,ix,hx;

    hx = __HI(x);       /* high word of x */
    ix = hx&0x7fffffff;
    if(ix<=0x3fe921fb)   /* |x| ~<= pi/4 , no need for reduction */
    {y[0] = x; y[1] = 0; return 0;}
    if(ix<0x4002d97c) {  /* |x| < 3pi/4, special case with n=+-1 */
        if(hx>0) { 
            z = x - pio2_1;
            if(ix!=0x3ff921fb) {    /* 33+53 bit pi is good enough */
                y[0] = z - pio2_1t;
                y[1] = (z-y[0])-pio2_1t;
            } else {        /* near pi/2, use 33+33+53 bit pi */
                z -= pio2_2;
                y[0] = z - pio2_2t;
                y[1] = (z-y[0])-pio2_2t;
            }
            return 1;
        } else {    /* negative x */
            z = x + pio2_1;
            if(ix!=0x3ff921fb) {    /* 33+53 bit pi is good enough */
                y[0] = z + pio2_1t;
                y[1] = (z-y[0])+pio2_1t;
            } else {        /* near pi/2, use 33+33+53 bit pi */
                z += pio2_2;
                y[0] = z + pio2_2t;
                y[1] = (z-y[0])+pio2_2t;
            }
            return -1;
        }
    }
    if(ix<=0x413921fb) { /* |x| ~<= 2^19*(pi/2), medium size */
        t  = fabs(x);
        n  = (int) (t*invpio2+half);
        fn = (double)n;
        r  = t-fn*pio2_1;
        w  = fn*pio2_1t;    /* 1st round good to 85 bit */
        if(n<32&&ix!=npio2_hw[n-1]) {   
            y[0] = r-w; /* quick check no cancellation */
        } else {
            j  = ix>>20;
            y[0] = r-w; 
            i = j-(((__HI(y[0]))>>20)&0x7ff);
            if(i>16) {  /* 2nd iteration needed, good to 118 */
                t  = r;
                w  = fn*pio2_2; 
                r  = t-w;
                w  = fn*pio2_2t-((t-r)-w);  
                y[0] = r-w;
                i = j-(((__HI(y[0]))>>20)&0x7ff);
                if(i>49)  { /* 3rd iteration need, 151 bits acc */
                    t  = r; /* will cover all possible cases */
                    w  = fn*pio2_3; 
                    r  = t-w;
                    w  = fn*pio2_3t-((t-r)-w);  
                    y[0] = r-w;
                }
            }
        }
        y[1] = (r-y[0])-w;
        if(hx<0)    {y[0] = -y[0]; y[1] = -y[1]; return -n;}
        else     return n;
    }
    /* 
     * all other (large) arguments
     */
    if(ix>=0x7ff00000) {        /* x is inf or NaN */
        y[0]=y[1]=x-x; return 0;
    }
    /* set z = scalbn(|x|,ilogb(x)-23) */
    __LO(z) = __LO(x);
    e0  = (ix>>20)-1046;    /* e0 = ilogb(z)-23; */
    __HI(z) = ix - (e0<<20);
    for(i=0;i<2;i++) {
        tx[i] = (double)((int)(z));
        z     = (z-tx[i])*two24;
    }
    tx[2] = z;
    nx = 3;
    while(tx[nx-1]==zero) nx--; /* skip zero term */
    n  =  __kernel_rem_pio2(tx,y,e0,nx,2,two_over_pi);
    if(hx<0) {y[0] = -y[0]; y[1] = -y[1]; return -n;}
    return n;
}
















static const double 
S1  = -1.66666666666666324348e-01, /* 0xBFC55555, 0x55555549 */
    S2  =  8.33333333332248946124e-03, /* 0x3F811111, 0x1110F8A6 */
    S3  = -1.98412698298579493134e-04, /* 0xBF2A01A0, 0x19C161D5 */
    S4  =  2.75573137070700676789e-06, /* 0x3EC71DE3, 0x57B1FE7D */
    S5  = -2.50507602534068634195e-08, /* 0xBE5AE5E6, 0x8A2B9CEB */
    S6  =  1.58969099521155010221e-10; /* 0x3DE5D93A, 0x5ACFD57C */

double __kernel_sin(double x, double y, int iy)
{
    double z,r,v;
    int ix;
    ix = __HI(x)&0x7fffffff;    /* high word of x */
    if(ix<0x3e400000)           /* |x| < 2**-27 */
    {if((int)x==0) return x;}        /* generate inexact */
    z   =  x*x;
    v   =  z*x;
    r   =  S2+z*(S3+z*(S4+z*(S5+z*S6)));
    if(iy==0) return x+v*(S1+z*r);
    else      return x-((z*(half*y-v*r)-y)-v*S1);
}

static const double 
C1  =  4.16666666666666019037e-02, /* 0x3FA55555, 0x5555554C */
    C2  = -1.38888888888741095749e-03, /* 0xBF56C16C, 0x16C15177 */
    C3  =  2.48015872894767294178e-05, /* 0x3EFA01A0, 0x19CB1590 */
    C4  = -2.75573143513906633035e-07, /* 0xBE927E4F, 0x809C52AD */
    C5  =  2.08757232129817482790e-09, /* 0x3E21EE9E, 0xBDB4B1C4 */
    C6  = -1.13596475577881948265e-11; /* 0xBDA8FAE9, 0xBE8838D4 */

double __kernel_cos(double x, double y)
{
    double a,hz,z,r,qx;
    int ix;
    ix = __HI(x)&0x7fffffff;    /* ix = |x|'s high word*/
    if(ix<0x3e400000) {         /* if x < 2**27 */
        if(((int)x)==0) return one;     /* generate inexact */
    }
    z  = x*x;
    r  = z*(C1+z*(C2+z*(C3+z*(C4+z*(C5+z*C6)))));
    if(ix < 0x3FD33333)             /* if |x| < 0.3 */ 
        return one - (0.5*z - (z*r - x*y));
    else {
        if(ix > 0x3fe90000) {       /* x > 0.78125 */
            qx = 0.28125;
        } else {
            __HI(qx) = ix-0x00200000;   /* x/4 */
            __LO(qx) = 0;
        }
        hz = 0.5*z-qx;
        a  = one-qx;
        return a - (hz - (z*r-x*y));
    }
}


double sin(double x)
{
    double y[2],z=0.0;
    int n, ix;

    /* High word of x. */
    ix = __HI(x);

    /* |x| ~< pi/4 */
    ix &= 0x7fffffff;
    if(ix <= 0x3fe921fb) return __kernel_sin(x,z,0);

    /* sin(Inf or NaN) is NaN */
    else if (ix>=0x7ff00000) return x-x;

    /* argument reduction needed */
    else {
        n = __ieee754_rem_pio2(x,y);
        switch(n&3) {
            case 0: return  __kernel_sin(y[0],y[1],1);
            case 1: return  __kernel_cos(y[0],y[1]);
            case 2: return -__kernel_sin(y[0],y[1],1);
            default:
                    return -__kernel_cos(y[0],y[1]);
        }
    }
}

double cos(double x)
{
    double y[2],z=0.0;
    int n, ix;

    /* High word of x. */
    ix = __HI(x);

    /* |x| ~< pi/4 */
    ix &= 0x7fffffff;
    if(ix <= 0x3fe921fb) return __kernel_cos(x,z);

    /* cos(Inf or NaN) is NaN */
    else if (ix>=0x7ff00000) return x-x;

    /* argument reduction needed */
    else {
        n = __ieee754_rem_pio2(x,y);
        switch(n&3) {
            case 0: return  __kernel_cos(y[0],y[1]);
            case 1: return -__kernel_sin(y[0],y[1],1);
            case 2: return -__kernel_cos(y[0],y[1]);
            default:
                    return  __kernel_sin(y[0],y[1],1);
        }
    }
}

double w_sin(double x)
{
    return sin(x);
}

double w_cos(double x)
{
    return cos(x);
}

static const double
pi =  3.14159265358979311600e+00, /* 0x400921FB, 0x54442D18 */
   pio2_hi =  1.57079632679489655800e+00, /* 0x3FF921FB, 0x54442D18 */
   pio2_lo =  6.12323399573676603587e-17, /* 0x3C91A626, 0x33145C07 */
   pS0 =  1.66666666666666657415e-01, /* 0x3FC55555, 0x55555555 */
   pS1 = -3.25565818622400915405e-01, /* 0xBFD4D612, 0x03EB6F7D */
   pS2 =  2.01212532134862925881e-01, /* 0x3FC9C155, 0x0E884455 */
   pS3 = -4.00555345006794114027e-02, /* 0xBFA48228, 0xB5688F3B */
   pS4 =  7.91534994289814532176e-04, /* 0x3F49EFE0, 0x7501B288 */
   pS5 =  3.47933107596021167570e-05, /* 0x3F023DE1, 0x0DFDF709 */
   qS1 = -2.40339491173441421878e+00, /* 0xC0033A27, 0x1C8A2D4B */
   qS2 =  2.02094576023350569471e+00, /* 0x40002AE5, 0x9C598AC8 */
   qS3 = -6.88283971605453293030e-01, /* 0xBFE6066C, 0x1B8D0159 */
   qS4 =  7.70381505559019352791e-02; /* 0x3FB3B8C5, 0xB12E9282 */

double __ieee754_acos(double x)
{
    double z,p,q,r,w,s,c,df;
    int hx,ix;
    hx = __HI(x);
    ix = hx&0x7fffffff;
    if(ix>=0x3ff00000) {    /* |x| >= 1 */
        if(((ix-0x3ff00000)|__LO(x))==0) {  /* |x|==1 */
            if(hx>0) return 0.0;        /* acos(1) = 0  */
            else return pi+2.0*pio2_lo; /* acos(-1)= pi */
        }
        return (x-x)/(x-x);     /* acos(|x|>1) is NaN */
    }
    if(ix<0x3fe00000) { /* |x| < 0.5 */
        if(ix<=0x3c600000) return pio2_hi+pio2_lo;/*if|x|<2**-57*/
        z = x*x;
        p = z*(pS0+z*(pS1+z*(pS2+z*(pS3+z*(pS4+z*pS5)))));
        q = one+z*(qS1+z*(qS2+z*(qS3+z*qS4)));
        r = p/q;
        return pio2_hi - (x - (pio2_lo-x*r));
    } else  if (hx<0) {     /* x < -0.5 */
        z = (one+x)*0.5;
        p = z*(pS0+z*(pS1+z*(pS2+z*(pS3+z*(pS4+z*pS5)))));
        q = one+z*(qS1+z*(qS2+z*(qS3+z*qS4)));
        s = sqrt(z);
        r = p/q;
        w = r*s-pio2_lo;
        return pi - 2.0*(s+w);
    } else {            /* x > 0.5 */
        z = (one-x)*0.5;
        s = sqrt(z);
        df = s;
        __LO(df) = 0;
        c  = (z-df*df)/(s+df);
        p = z*(pS0+z*(pS1+z*(pS2+z*(pS3+z*(pS4+z*pS5)))));
        q = one+z*(qS1+z*(qS2+z*(qS3+z*qS4)));
        r = p/q;
        w = r*s+c;
        return 2.0*(df+w);
    }
}

double acos(double x)
{
    return __ieee754_acos(x);
}


/* ===-- powidf2.cpp - Implement __powidf2 ---------------------------------===
 *
 *                     The LLVM Compiler Infrastructure
 *
 * This file is dual licensed under the MIT and the University of Illinois Open
 * Source Licenses. See LICENSE.TXT for details.
 *
 * ===----------------------------------------------------------------------===
 *
 * This file implements __powidf2 for the compiler_rt library.
 *
 * ===----------------------------------------------------------------------===
 */
/* Returns: a ^ b */
double __powidf2(double a, int b)
{
    const int recip = b < 0;
    double r = 1;
    while (1)
    {
        if (b & 1)
            r *= a;
        b /= 2;
        if (b == 0)
            break;
        a *= a;
    }
    return recip ? 1/r : r;
}

static const double
bp[] = {1.0, 1.5,},
    dp_h[] = { 0.0, 5.84962487220764160156e-01,}, /* 0x3FE2B803, 0x40000000 */
    dp_l[] = { 0.0, 1.35003920212974897128e-08,}, /* 0x3E4CFDEB, 0x43CFD006 */
    two =  2.0,
    two53   =  9007199254740992.0,  /* 0x43400000, 0x00000000 */
    /* poly coefs for (3/2)*(log(x)-2s-2/3*s**3 */
    L1  =  5.99999999999994648725e-01, /* 0x3FE33333, 0x33333303 */
    L2  =  4.28571428578550184252e-01, /* 0x3FDB6DB6, 0xDB6FABFF */
    L3  =  3.33333329818377432918e-01, /* 0x3FD55555, 0x518F264D */
    L4  =  2.72728123808534006489e-01, /* 0x3FD17460, 0xA91D4101 */
    L5  =  2.30660745775561754067e-01, /* 0x3FCD864A, 0x93C9DB65 */
    L6  =  2.06975017800338417784e-01, /* 0x3FCA7E28, 0x4A454EEF */
    P1   =  1.66666666666666019037e-01, /* 0x3FC55555, 0x5555553E */
    P2   = -2.77777777770155933842e-03, /* 0xBF66C16C, 0x16BEBD93 */
    P3   =  6.61375632143793436117e-05, /* 0x3F11566A, 0xAF25DE2C */
    P4   = -1.65339022054652515390e-06, /* 0xBEBBBD41, 0xC5D26BF1 */
    P5   =  4.13813679705723846039e-08, /* 0x3E663769, 0x72BEA4D0 */
    lg2  =  6.93147180559945286227e-01, /* 0x3FE62E42, 0xFEFA39EF */
    lg2_h  =  6.93147182464599609375e-01, /* 0x3FE62E43, 0x00000000 */
    lg2_l  = -1.90465429995776804525e-09, /* 0xBE205C61, 0x0CA86C39 */
    ovt =  8.0085662595372944372e-0017, /* -(1024-log2(ovfl+.5ulp)) */
    cp    =  9.61796693925975554329e-01, /* 0x3FEEC709, 0xDC3A03FD =2/(3ln2) */
    cp_h  =  9.61796700954437255859e-01, /* 0x3FEEC709, 0xE0000000 =(float)cp */
    cp_l  = -7.02846165095275826516e-09, /* 0xBE3E2FE0, 0x145B01F5 =tail of cp_h*/
    ivln2    =  1.44269504088896338700e+00, /* 0x3FF71547, 0x652B82FE =1/ln2 */
    ivln2_h  =  1.44269502162933349609e+00, /* 0x3FF71547, 0x60000000 =24b 1/ln2*/
    ivln2_l  =  1.92596299112661746887e-08; /* 0x3E54AE0B, 0xF85DDF44 =1/ln2 tail*/


double __ieee754_pow(double x, double y)
{
    double z,ax,z_h,z_l,p_h,p_l;
    double y1,t1,t2,r,s,t,u,v,w;
    int i0,i1,i,j,k,yisint,n;
    int hx,hy,ix,iy;
    unsigned lx,ly;

    i0 = ((*(int*)&one)>>29)^1; i1=1-i0;
    hx = __HI(x); lx = __LO(x);
    hy = __HI(y); ly = __LO(y);
    ix = hx&0x7fffffff;  iy = hy&0x7fffffff;

    /* y==zero: x**0 = 1 */
    if((iy|ly)==0) return one;  

    /* +-NaN return x+y */
    if(ix > 0x7ff00000 || ((ix==0x7ff00000)&&(lx!=0)) ||
            iy > 0x7ff00000 || ((iy==0x7ff00000)&&(ly!=0))) 
        return x+y; 

    /* determine if y is an odd int when x < 0
     * yisint = 0   ... y is not an integer
     * yisint = 1  ... y is an odd int
     * yisint = 2 ... y is an even int
     */
    yisint  = 0;
    if(hx<0) {  
        if(iy>=0x43400000) yisint = 2; /* even integer y */
        else if(iy>=0x3ff00000) {
            k = (iy>>20)-0x3ff;    /* exponent */
            if(k>20) {
                j = ly>>(52-k);
                if((j<<(52-k))==ly) yisint = 2-(j&1);
            } else if(ly==0) {
                j = iy>>(20-k);
                if((j<<(20-k))==iy) yisint = 2-(j&1);
            }
        }       
    } 

    /* special value of y */
    if(ly==0) {     
        if (iy==0x7ff00000) {   /* y is +-inf */
            if(((ix-0x3ff00000)|lx)==0)
                return  y - y;  /* inf**+-1 is NaN */
            else if (ix >= 0x3ff00000)/* (|x|>1)**+-inf = inf,0 */
                return (hy>=0)? y: zero;
            else            /* (|x|<1)**-,+inf = inf,0 */
                return (hy<0)?-y: zero;
        } 
        if(iy==0x3ff00000) {    /* y is  +-1 */
            if(hy<0) return one/x; else return x;
        }
        if(hy==0x40000000) return x*x; /* y is  2 */
        if(hy==0x3fe00000) {    /* y is  0.5 */
            if(hx>=0)   /* x >= +0 */
                return sqrt(x); 
        }
    }

    ax   = fabs(x);
    /* special value of x */
    if(lx==0) {
        if(ix==0x7ff00000||ix==0||ix==0x3ff00000){
            z = ax;         /*x is +-0,+-inf,+-1*/
            if(hy<0) z = one/z; /* z = (1/|x|) */
            if(hx<0) {
                if(((ix-0x3ff00000)|yisint)==0) {
                    z = (z-z)/(z-z); /* (-1)**non-int is NaN */
                } else if(yisint==1) 
                    z = -z;     /* (x<0)**odd = -(|x|**odd) */
            }
            return z;
        }
    }

    n = (hx>>31)+1;

    /* (x<0)**(non-int) is NaN */
    if((n|yisint)==0) return (x-x)/(x-x);

    s = one; /* s (sign of result -ve**odd) = -1 else = 1 */
    if((n|(yisint-1))==0) s = -one;/* (-ve)**(odd int) */

    /* |y| is huge */
    if(iy>0x41e00000) { /* if |y| > 2**31 */
        if(iy>0x43f00000){  /* if |y| > 2**64, must o/uflow */
            if(ix<=0x3fefffff) return (hy<0)? huge*huge:tiny*tiny;
            if(ix>=0x3ff00000) return (hy>0)? huge*huge:tiny*tiny;
        }
        /* over/underflow if x is not close to one */
        if(ix<0x3fefffff) return (hy<0)? s*huge*huge:s*tiny*tiny;
        if(ix>0x3ff00000) return (hy>0)? s*huge*huge:s*tiny*tiny;
        /* now |1-x| is tiny <= 2**-20, suffice to compute 
           log(x) by x-x^2/2+x^3/3-x^4/4 */
        t = ax-one;     /* t has 20 trailing zeros */
        w = (t*t)*(0.5-t*(0.3333333333333333333333-t*0.25));
        u = ivln2_h*t;  /* ivln2_h has 21 sig. bits */
        v = t*ivln2_l-w*ivln2;
        t1 = u+v;
        __LO(t1) = 0;
        t2 = v-(t1-u);
    } else {
        double ss,s2,s_h,s_l,t_h,t_l;
        n = 0;
        /* take care subnormal number */
        if(ix<0x00100000)
        {ax *= two53; n -= 53; ix = __HI(ax); }
        n  += ((ix)>>20)-0x3ff;
        j  = ix&0x000fffff;
        /* determine interval */
        ix = j|0x3ff00000;      /* normalize ix */
        if(j<=0x3988E) k=0;     /* |x|<sqrt(3/2) */
        else if(j<0xBB67A) k=1; /* |x|<sqrt(3)   */
        else {k=0;n+=1;ix -= 0x00100000;}
        __HI(ax) = ix;

        /* compute ss = s_h+s_l = (x-1)/(x+1) or (x-1.5)/(x+1.5) */
        u = ax-bp[k];       /* bp[0]=1.0, bp[1]=1.5 */
        v = one/(ax+bp[k]);
        ss = u*v;
        s_h = ss;
        __LO(s_h) = 0;
        /* t_h=ax+bp[k] High */
        t_h = zero;
        __HI(t_h)=((ix>>1)|0x20000000)+0x00080000+(k<<18); 
        t_l = ax - (t_h-bp[k]);
        s_l = v*((u-s_h*t_h)-s_h*t_l);
        /* compute log(ax) */
        s2 = ss*ss;
        r = s2*s2*(L1+s2*(L2+s2*(L3+s2*(L4+s2*(L5+s2*L6)))));
        r += s_l*(s_h+ss);
        s2  = s_h*s_h;
        t_h = 3.0+s2+r;
        __LO(t_h) = 0;
        t_l = r-((t_h-3.0)-s2);
        /* u+v = ss*(1+...) */
        u = s_h*t_h;
        v = s_l*t_h+t_l*ss;
        /* 2/(3log2)*(ss+...) */
        p_h = u+v;
        __LO(p_h) = 0;
        p_l = v-(p_h-u);
        z_h = cp_h*p_h;     /* cp_h+cp_l = 2/(3*log2) */
        z_l = cp_l*p_h+p_l*cp+dp_l[k];
        /* log2(ax) = (ss+..)*2/(3*log2) = n + dp_h + z_h + z_l */
        t = (double)n;
        t1 = (((z_h+z_l)+dp_h[k])+t);
        __LO(t1) = 0;
        t2 = z_l-(((t1-t)-dp_h[k])-z_h);
    }

    /* split up y into y1+y2 and compute (y1+y2)*(t1+t2) */
    y1  = y;
    __LO(y1) = 0;
    p_l = (y-y1)*t1+y*t2;
    p_h = y1*t1;
    z = p_l+p_h;
    j = __HI(z);
    i = __LO(z);
    if (j>=0x40900000) {                /* z >= 1024 */
        if(((j-0x40900000)|i)!=0)           /* if z > 1024 */
            return s*huge*huge;         /* overflow */
        else {
            if(p_l+ovt>z-p_h) return s*huge*huge;   /* overflow */
        }
    } else if((j&0x7fffffff)>=0x4090cc00 ) {    /* z <= -1075 */
        if(((j-0xc090cc00)|i)!=0)       /* z < -1075 */
            return s*tiny*tiny;     /* underflow */
        else {
            if(p_l<=z-p_h) return s*tiny*tiny;  /* underflow */
        }
    }
    /*
     * compute 2**(p_h+p_l)
     */
    i = j&0x7fffffff;
    k = (i>>20)-0x3ff;
    n = 0;
    if(i>0x3fe00000) {      /* if |z| > 0.5, set n = [z+0.5] */
        n = j+(0x00100000>>(k+1));
        k = ((n&0x7fffffff)>>20)-0x3ff; /* new k for n */
        t = zero;
        __HI(t) = (n&~(0x000fffff>>k));
        n = ((n&0x000fffff)|0x00100000)>>(20-k);
        if(j<0) n = -n;
        p_h -= t;
    } 
    t = p_l+p_h;
    __LO(t) = 0;
    u = t*lg2_h;
    v = (p_l-(t-p_h))*lg2+t*lg2_l;
    z = u+v;
    w = v-(z-u);
    t  = z*z;
    t1  = z - t*(P1+t*(P2+t*(P3+t*(P4+t*P5))));
    r  = (z*t1)/(t1-two)-(w+z*w);
    z  = one-(r-z);
    j  = __HI(z);
    j += (n<<20);
    if((j>>20)<=0) z = scalbn(z,n); /* subnormal output */
    else __HI(z) += (n<<20);
    return s*z;
}

double pow(double x, double y)  /* wrapper pow */
{
    return  __ieee754_pow(x,y);
}

/*
   int main()
   {
   double a = 3.14;
   double b = 0.0;
   b = cos(a);
   printf("%f\n", b);
   return 0;
   }
 */
