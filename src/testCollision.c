#ifdef TARGET_TEST
#include <stdio.h>
#include "spriteConstants.h"
#include "gameState.h"
#include "gPngGame.h"
#include "gPngGraphics.h"
#include "commonTest.h"
#include "gamePhysicsStructs.h"
#include <assert.h>

Ball ball;
Paddle paddleOne;
Paddle paddleTwo;
Court court;
GPngGame gPngGame;

void testCornerCaseCollision(void);
void initGameObjects(void);
int main() {
    testCornerCaseCollision();
    return 1;

}

void testCornerCaseCollision() {
    setupSpriteMemPtrs();
    fillSpriteMem();

    initGameObjects();

    while(1) {
	updatePongGame(&gPngGame);
	drawBall(&ball);
	drawPaddleSprites(&paddleOne, &paddleTwo);
    }
	
}

void initGameObjects() {
    int xCalc;
    initDefaultBall(&ball);
    initDefaultCourt(&court);
    initDefaultPaddleOne(&paddleOne);
    initDefaultPaddleTwo(&paddleTwo);
    
    gPngGame.isPlayerOneHuman = 0;
    gPngGame.isPlayerTwoHuman = 0;
    
    xCalc = 320l+50l-50l;
    paddleTwo.x = FPMAKE(xCalc, 0);
    ball.x = FPMAKE(xCalc-7-20,0);

    paddleTwo.y = FPMAKE(102, 0);
    ball.y = FPMAKE(117l - 10l, 0);

    setBallXVel(FPMAKE(2,0), &ball);
    setBallYVel(FPMAKE(2,0), &ball);

    setPaddleYVel(FPMAKE(1,0), &paddleTwo);
    gPngGame.ball = &ball;
    gPngGame.paddleOne = &paddleOne;
    gPngGame.paddleTwo = &paddleTwo;
    gPngGame.court = &court;
    gPngGame.useGravity = 1;
    gPngGame.gravity = -1;
    gPngGame.epsilon = FPMAKE(2,8);
    
}

#endif
