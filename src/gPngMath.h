#ifndef GRAVPNG_C64_H
#define GRAVPNG_C64_H

#ifdef TARGET_C64
typedef int GPINT;
typedef unsigned int GPUINT;
#define GPSHIFT (4)
#define GRAVITY (FPMAKE(0,8))

#define true (1)
#define false (0)
#define FPMUL(x,y)	(((x)*(y))>>4)

#define FPDIV(x,y)	((((x)<<1)/((y)>>1))>>2)


#define FPINT(x)        ((x>>GPSHIFT))
#define FPFLOATFRAC(x)  (x/(1<<GPSHIFT))
#define FPFRAC(x)       (x&((1<<GPSHIFT)-1))

#define FPMAKEINT(x)    ((x<<GPSHIFT))
#define FPMAKE(x,y)     ((x<<GPSHIFT)|y)
#else
#define INT_SIZE (4)
#define INT_SIZE_BITS (32)

typedef int GPINT;
typedef unsigned int GPUINT;
#define GPSHIFT (16)
#define GRAVITY (0xcccc)

#define FPMUL(x,y)	((((x)>>6)*((y)>>6))>>4)
#define FPMUL2(x,y) ((x*y)>>16)
#define FPDIV(x,y)	((((x)<<6)/((y)>>6))>>4)

#define FPINT(x)        ((x>>GPSHIFT))
#define FPFLOATFRAC(x)  (x/(1<<GPSHIFT))
#define FPFRAC(x)       (x&((1<<GPSHIFT)-1))

#define FPMAKEINT(x)    ((x<<GPSHIFT))
#define FPMAKE(x,y)     ((x<<GPSHIFT)|y)


#endif

#endif

