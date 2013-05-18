#ifdef TARGET_TEST
#include "gPngGraphics.h"
#include "gameObjects.h"
#include "gamePhysics.h"
#include "commonTest.h"
#include "spriteConstants.h"
#include "gameState.h"
#include "gPngGraphics.h"
#include "gPngGame.h"
#include "gPngStructPrint.h"

Ball ball;
Paddle paddleOne;
Paddle paddleTwo;
Court court;
GPngGame gPngGame;

void testGameGraphics();
void setupGraphics();
void initGameObjects(StartState startState);
int handlePlayerInputTestGraphics(int *startStateIndex);

int main()
{
    testGameGraphics();
    return 1;

}

void testGameGraphics()
{
    StartState startStates[3] = {paddlesMaxHorizontal, paddlesMaxNorth, paddlesMaxSouth};
    int startStatesLength = 3;
    int startStateIndex = 0;

    setupSpriteMemPtrs();
    fillSpriteMem();
    
    initGameObjects(startStates[startStateIndex]);
    
    printPaddle(&paddleTwo);
    printBall(&ball);
    
    while(1){
	
	if(handlePlayerInputTestGraphics(&startStateIndex)) {
	    printf("startStateIndex %d\n", startStateIndex);
	    if(startStateIndex >= startStatesLength) {
		return;
	    }
	    initGameObjects(startStates[startStateIndex]);
	    printPaddle(&paddleOne);
	}
	
	drawBall(&ball);
	drawPaddleSprites(&paddleOne, &paddleTwo);
    }

}

int handlePlayerInputTestGraphics(int *startStateIndex)
{
    char joystickEvent;
    char *dataPortA = (char*) 0xdc00;
    joystickEvent = *(dataPortA);
    
    if (!(joystickEvent & 16)) {
	(*startStateIndex)++;
	return 1;
    } else {
	return 0;
    }
}

void initGameObjects(StartState startState)
{
    initDefaultBall(&ball);
    initDefaultCourt(&court);
    initDefaultPaddleOne(&paddleOne);
    initDefaultPaddleTwo(&paddleTwo);
    gPngGame.ball = &ball;
    gPngGame.paddleOne = &paddleOne;
    gPngGame.paddleTwo = &paddleTwo;
    gPngGame.court = &court;

    switch(startState) {
    case paddlesMaxHorizontal:
	paddleOne.x = FPMAKE(FPINT(gPngGame.court->x), 0);
	paddleOne.y = FPMAKE(FPINT(gPngGame.court->y), 0);
	paddleTwo.x = FPMAKE(FPINT(gPngGame.court->width+gPngGame.court->x)-DEFAULT_PADDLE_WIDTH,0);
	paddleTwo.y = FPMAKE(FPINT(gPngGame.court->y), 0);
	break;
    case paddlesMaxNorth: 

	break;
    case paddlesMaxSouth:
	paddleOne.y = FPMAKE(FPINT(gPngGame.court->height+gPngGame.court->y)-DEFAULT_PADDLE_HEIGHT,0);
	paddleTwo.y = FPMAKE(FPINT(gPngGame.court->height+gPngGame.court->y)-DEFAULT_PADDLE_HEIGHT,0);
	break;
	
    case noStartState:

	break;
    default:
	printf("default - please provide a valid value");
	break;
    }
 }

#endif
