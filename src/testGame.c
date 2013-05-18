#ifdef TARGET_TEST
#include "testGame.h"

#ifdef TARGET_C64
int main()
{
    printf("size of: char: %u, short: %u, int: %u long: %u", sizeof(char), sizeof(short), sizeof(int), sizeof(long));
    //   collidePaddleOneWithCourt_shouldZeroVelAndResetPositions();
    collidePaddleOneWithCourt_shouldNotDoAnythingIfNoColl();
    collidePaddleOneWithCourt_shouldReturnCorrectCD();

    collidePaddleTwoWithCourt_shouldZeroVelAndResetPositions();
    collidePaddleTwoWithCourt_shouldReturnCorrectCD();
    collidePaddleTwoWithCourt_shouldNotDoAnythingIfNoColl();


}
#endif

void collidePaddleTwoWithCourt_shouldReturnCorrectCD(void)
{
    Paddle paddle2;
    Court court;
    CollisionDirection cd;

    initDefaultCourt(&court);
    initDefaultPaddleTwo(&paddle2);
    
    paddle2.x = FPMAKE(-1,0);
    paddle2.y = FPMAKE(-1,0);
    cd = collidePaddleTwoWithCourt(&paddle2, &court);
    assert(cd == nWCollision);

    paddle2.x = FPMAKE(-1,0);
    paddle2.y = FPMAKE(0,0);
    cd = collidePaddleTwoWithCourt(&paddle2, &court);
    assert(cd == wCollision);
    
    paddle2.x = FPMAKE(-1,0);
    paddle2.y = FPMAKE(1000,0);
    cd = collidePaddleTwoWithCourt(&paddle2, &court);
    assert(cd == sWCollision);

    paddle2.x = FPMAKE(DEFAULT_RIGHT_ACCAREA_X, 0);
    paddle2.y = FPMAKE(-1,0);
    cd = collidePaddleTwoWithCourt(&paddle2, &court);
    assert(cd == nCollision);

    paddle2.x = FPMAKE(DEFAULT_RIGHT_ACCAREA_X, 0);
    paddle2.y = FPMAKE(0,0);
    cd = collidePaddleTwoWithCourt(&paddle2, &court);
    assert(cd == noCollision);

    paddle2.x = FPMAKE(DEFAULT_RIGHT_ACCAREA_X,0);
    paddle2.y = FPMAKE(1000,0);
    cd = collidePaddleTwoWithCourt(&paddle2, &court);
    assert(cd == sCollision);
    
    paddle2.x = FPMAKE(1000,0);
    paddle2.y = FPMAKE(-1,0);
    cd = collidePaddleTwoWithCourt(&paddle2, &court);
    assert(cd == nECollision);

    paddle2.x = FPMAKE(1000,0);
    paddle2.y = FPMAKE(0,0);
    cd = collidePaddleTwoWithCourt(&paddle2, &court);
    assert(cd == eCollision);

    paddle2.x = FPMAKE(1000,0);
    paddle2.y = FPMAKE(1000,0);
    cd = collidePaddleTwoWithCourt(&paddle2, &court);
    assert(cd == sECollision);
}

void collidePaddleOneWithCourt_shouldReturnCorrectCD(void)
{
    Paddle paddle1;
    Court court;
    CollisionDirection cd;

    initDefaultCourt(&court);
    initDefaultPaddleOne(&paddle1);

    paddle1.x = FPMAKE(-1,0);
    paddle1.y = FPMAKE(-1,0);
    cd = collidePaddleOneWithCourt(&paddle1, &court);
    assert(cd == nWCollision);
    
    paddle1.x = FPMAKE(-1,0);
    paddle1.y = FPMAKE(0,0);
    cd = collidePaddleOneWithCourt(&paddle1, &court);
    assert(cd == wCollision);

    paddle1.x = FPMAKE(-1,0);
    paddle1.y = FPMAKE(1000,0);
    cd = collidePaddleOneWithCourt(&paddle1, &court);
    assert(cd == sWCollision);

    paddle1.x = FPMAKE(0,0);
    paddle1.y = FPMAKE(-1,0);
    cd = collidePaddleOneWithCourt(&paddle1, &court);
    assert(cd == nCollision);

    paddle1.x = FPMAKE(0,0);
    paddle1.y = FPMAKE(0,0);
    cd = collidePaddleOneWithCourt(&paddle1, &court);
    assert(cd == noCollision);

    paddle1.x = FPMAKE(0,0);
    paddle1.y = FPMAKE(1000,0);
    cd = collidePaddleOneWithCourt(&paddle1, &court);
    assert(cd == sCollision);

    paddle1.x = FPMAKE(1000,0);
    paddle1.y = FPMAKE(-1,0);
    cd = collidePaddleOneWithCourt(&paddle1, &court);
    assert(cd == nECollision);

    paddle1.x = FPMAKE(1000,0);
    paddle1.y = FPMAKE(0,0);
    cd = collidePaddleOneWithCourt(&paddle1, &court);
    assert(cd == eCollision);

    paddle1.x = FPMAKE(1000,0);
    paddle1.y = FPMAKE(1000,0);
    cd = collidePaddleOneWithCourt(&paddle1, &court);
    assert(cd == sECollision);
}

void collidePaddleOneWithCourt_shouldNotDoAnythingIfNoColl(void)
{
    Paddle paddle1;
    Court court;
    CollisionDirection cd;

    initDefaultCourt(&court);
    initDefaultPaddleOne(&paddle1);

    printPaddle(&paddle1);
   // printf(":::paddle1->x %d\n", paddle1.x);
    cd = collidePaddleOneWithCourt(&paddle1, &court);
    printPaddle(&paddle1);
    printCourt(&court);

    assert(cd == noCollision);
    
}

void collidePaddleTwoWithCourt_shouldNotDoAnythingIfNoColl(void)
{
    Paddle paddle2;
    Court court;
    CollisionDirection cd;

    initDefaultCourt(&court);
    initDefaultPaddleTwo(&paddle2);
    
    cd = collidePaddleTwoWithCourt(&paddle2, &court);
    assert(cd == noCollision);
}

void collidePaddleOneWithCourt_shouldZeroVelAndResetPositions(void)
{
    Paddle paddle1;
    Court court;
    CollisionDirection cd;
    
    
    initDefaultCourt(&court);
    initDefaultPaddleOne(&paddle1);
    
    paddle1.x = FPMAKE(-1,0);
    paddle1.y = FPMAKE(-1,0);
    paddle1.xVel = FPMAKE(10,0);
    paddle1.yVel = FPMAKE(10,0);

    cd = collidePaddleOneWithCourt(&paddle1, &court);
    assert(paddle1.x >= 0 && paddle1.x + paddle1.width <= court.leftAccAreaWidth);
    assert(paddle1.y >= 0 && paddle1.y + paddle1.height <= court.height);
    assert(paddle1.yVel == 0);
    assert(paddle1.xVel == 0);

    printf("cd: %d\n", cd);
    assert(cd == nWCollision);
}

void collidePaddleTwoWithCourt_shouldZeroVelAndResetPositions(void)
{
    Paddle paddle2;
    Court court;
    CollisionDirection cd;
    
    initDefaultCourt(&court);
    initDefaultPaddleTwo(&paddle2);

    paddle2.x = FPMAKE(-1,0);
    paddle2.y = FPMAKE(-1,0);
    paddle2.xVel = FPMAKE(10,0);
    paddle2.yVel = FPMAKE(10,0);

    cd = collidePaddleTwoWithCourt(&paddle2, &court);
    printPaddle(&paddle2);

    assert(paddle2.x >= 0 && paddle2.x + paddle2.width <= 
	   court.rightAccAreaWidth + court.rightAccAreaX);
    assert(paddle2.y >= 0 && paddle2.y + paddle2.height <= court.height);
    assert(paddle2.yVel == 0);
    assert(paddle2.xVel == 0);

    printf("cd: %d\n", cd);
    assert(cd == nWCollision);

}

#endif
