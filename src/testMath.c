#ifdef TARGET_TEST
#include <stdio.h>
#include "gPngMath.h"
#include <assert.h>


#define FPMUL_ONE_SHIFT(x,y)	(((x)*(y))>>4)
#define FPMUL_ORIG(x,y)	((((x)>>1)*((y)>>1))>>2)

void testFPMUL();

int main() {
    testFPMUL();
    return 1;

}

void testFPMUL() {
    
    int x, y, z, a, b, c;
    
    x = FPMAKE(1,0);
    y = FPMAKE(2,0);
    assert(FPMUL_ONE_SHIFT(x,y) == y);
    assert(FPMUL_ORIG(x,y) == y);

    x = FPMAKE(0, 8);
    y = FPMAKE(0, 8);
    z = FPMUL_ONE_SHIFT(x,y);
    printf("MUL x: %d.%d\n", FPINT(x), FPFRAC(x));
    printf("WIT y: %d.%d\n", FPINT(y), FPFRAC(y));
    printf("RES: %d.%d\n", FPINT(z), FPFRAC(z));
    assert(z == FPMAKE(0, 4));
    
    //orig mul
    x = FPMAKE(0, 8);
    y = FPMAKE(0, 8);
    z = FPMUL_ORIG(x,y);
    printf("MUL x: %d.%d\n", FPINT(x), FPFRAC(x));
    printf("WIT y: %d.%d\n", FPINT(y), FPFRAC(y));
    printf("RES: %d.%d\n", FPINT(z), FPFRAC(z));
    assert(z == FPMAKE(0, 4));

    x = FPMAKE(0, 1);
    y = FPMAKE(1, 0);
    z = FPMUL_ONE_SHIFT(x,y);
    printf("MUL x: %d.%d\n", FPINT(x), FPFRAC(x));
    printf("WIT y: %d.%d\n", FPINT(y), FPFRAC(y));
    printf("RES: %d.%d\n", FPINT(z), FPFRAC(z));
    assert(z == FPMAKE(0, 1));

    x = FPMAKE(0, 1);
    y = FPMAKE(1, 0);
    z = FPMUL_ORIG(x,y);
    printf("MUL x: %d.%d\n", FPINT(x), FPFRAC(x));
    printf("WIT y: %d.%d\n", FPINT(y), FPFRAC(y));
    printf("RES: %d.%d\n", FPINT(z), FPFRAC(z));
    //    assert(z == FPMAKE(0, 1));

}

#endif
