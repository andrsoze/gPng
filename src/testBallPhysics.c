#ifdef TARGET_TEST
#include "gamePhysics.h"
#include "gamePhysicsBall.h"
#include "gPngStructPrint.h"
#include <assert.h>

void testCollideBallWithPaddleOne();
void testCollideBallWithPaddleTwo();
void testCollideBallWithCourt();
int main()
{
    testCollideBallWithPaddleOne();
    testCollideBallWithPaddleTwo();
    testCollideBallWithCourt();
    return 1;
}

void testCollideBallWithPaddleOne()
{
    Ball ball;
    Paddle paddle1;

    initDefaultPaddleOne(&paddle1);
    initDefaultBall(&ball);

    printBall(&ball);
    printPaddle(&paddle1);

    collideBallWithPaddleOne(&ball, &paddle1, 0);
    
    printBall(&ball);
    printPaddle(&paddle1);
}

void testCollideBallWithPaddleTwo()
{
    Ball ball;
    Paddle paddle2;

    initDefaultPaddleTwo(&paddle2);
    initDefaultBall(&ball);

    printBall(&ball);
    printPaddle(&paddle2);

    collideBallWithPaddleTwo(&ball, &paddle2, 0);

    printBall(&ball);
    printPaddle(&paddle2);
}

void testCollideBallWithCourt()
{
    Ball ball;
    Court court;

    initDefaultBall(&ball);
    initDefaultCourt(&court);

    printBall(&ball);
    printCourt(&court);

    collideBallWithCourt(&ball, &court);

    printBall(&ball);
    printCourt(&court);
}


#endif
