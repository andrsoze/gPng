#ifdef TARGET_TEST
#include "testGameLoop.h"
#include "spriteConstants.h"
#include "gameState.h"
#include "gPngGraphics.h"
#include "gPngGame.h"
#include "player.h"
#include "commonTest.h"
#include <assert.h>

Ball ball;
Paddle paddleOne;
Paddle paddleTwo;
Court court;
GPngGame gPngGame;

void testBallMoves();
void initGameObjects(StartState startState);
void drawBallSprite(Ball *ball);

int main()
{
    testBallMoves();
    return 1;
}

void testBallMoves() {
    int startStateIndex, numStartStates;
    GravPngScoreChange scoreChange;

    #define NUM_START_STATES 10
    StartState startStates[NUM_START_STATES] = { straightLeftPaddleNonTopCollision, noStartState, straightRightNonTopCollision, straightLeftPaddleRearCollision, straightRightPaddleRearCollision, straightRightPaddleBottomCollision, straightRightPaddleTopCollision, straightLeftPaddleTopCollision, straightLeftPaddleBottomCollision}; 
    numStartStates = NUM_START_STATES;   
    startStateIndex = 0;
    setupSpriteMemPtrs();
    fillSpriteMem();
    
    initGameObjects(startStates[startStateIndex]);
    drawBall(&ball);
    drawPaddleSprites(&paddleOne, &paddleTwo);
    printPaddle(&paddleTwo);
    printBall(&ball); 
    printCourt(&court);

    while(1) {
	scoreChange = updatePongGame(&gPngGame);
	if(scoreChange == PLAYER_ONE_GOAL || scoreChange == PLAYER_TWO_GOAL) {
	    flashScreen();
	    startStateIndex++;
	    if(startStateIndex < numStartStates) {
		if(startStates[startStateIndex] == noStartState) {
		    resetPongGame(&gPngGame);
		    gPngGame.isPlayerOneHuman = true;
		} else {
		    initGameObjects(startStates[startStateIndex]);
		}
	    } else {
		return;
	    }
	    
	}
	
	if(startStates[startStateIndex] == noStartState) {
	    handlePlayerInput(&gPngGame, true);
	    //playerOneInput(&gPngGame);
	    playerTwoInput(&gPngGame);
	}
	
	drawBall(&ball);
	drawPaddleSprites(&paddleOne, &paddleTwo);
   } 
}

void drawBallSprite(Ball *ball) {
    unsigned int x, y;
    char *pokePtr;
    // calc x
    // first alt = INITIAL_ROW_SPACE*8+(21/2)
    // set x and y pos
    x = FPINT(ball->x);
    y = FPINT(ball->y);
    
    pokePtr = (char *) SP0X;
    *(pokePtr) = x;
    pokePtr = (char *) SP0Y;
    *(pokePtr) = y;
    
    //enable
    pokePtr = (char *) SP_ENABLE;
    *(pokePtr) |= 1;
}

void assembleDefaultPongGame() {
    gPngGame.ball = &ball;
    gPngGame.paddleOne = &paddleOne;
    gPngGame.paddleTwo = &paddleTwo;
    gPngGame.court = &court;
    gPngGame.useGravity = 1;
    gPngGame.gravity = 1;
    gPngGame.epsilon = FPMAKE(2,8);
}

void initGameObjects(StartState startState)
{
    initDefaultBall(&ball);
    initDefaultCourt(&court);
    initDefaultPaddleOne(&paddleOne);
    initDefaultPaddleTwo(&paddleTwo);

    gPngGame.isPlayerOneHuman = 0;
    gPngGame.isPlayerTwoHuman = 0;


    switch(startState) {
    case straightLeft:
	paddleTwo.x = FPMAKE(280,0);
	paddleTwo.y = FPMAKE(FPINT(gPngGame.court->y), 0);
	
	setBallXVel(-1*FPMAKE(0, 8), &ball);
	
	break;

    case straightLeftPaddleTopCollision:
	paddleTwo.x = FPMAKE(280,0);
	paddleTwo.y = FPMAKE(FPINT(gPngGame.court->y), 0);

	paddleOne.x = FPMAKE(35,0);
	paddleOne.y = FPMAKE(110,0);
	paddleOne.xVel = FPMAKE(0,0);
	paddleOne.yVel = FPMAKE(-1,0);
	ball.x = FPMAKE(45,0);
	ball.y = FPMAKE(100-DEFAULT_BALL_HEIGHT-8,0);
	ball.xVel = FPMAKE(-1,0);
	ball.yVel = FPMAKE(0,0);


	setBallXVel(-1*FPMAKE(0, 8), &ball);
	break;
    case straightLeftPaddleBottomCollision:
	paddleTwo.x = FPMAKE(280,0);
	paddleTwo.y = FPMAKE(FPINT(gPngGame.court->y), 0);

	paddleOne.x = FPMAKE(35,0);
	paddleOne.y = FPMAKE(90,0);
	paddleOne.xVel = FPMAKE(0,0);
	paddleOne.yVel = FPMAKE(1,0);
	ball.x = FPMAKE(45,0);
	ball.y = FPMAKE(100+DEFAULT_PADDLE_HEIGHT+8,0);
	ball.xVel = FPMAKE(-1,0);
	ball.yVel = FPMAKE(0,0);

	setBallXVel(-1*FPMAKE(0, 8), &ball);
	
	break;
    case straightLeftPaddleNonTopCollision:
	paddleOne.x = FPMAKE(24,0);
	paddleOne.y = FPMAKE(100,0);
	paddleOne.yVel = 0;
	paddleOne.xVel = MAX_PADDLE_SPEED_X;
	
	ball.x = FPMAKE(34+DEFAULT_PADDLE_WIDTH,0);
	ball.y = FPMAKE(100-DEFAULT_BALL_HEIGHT+1, 0);
	ball.xVel = MIN_BALL_SPEED_X;
	ball.yVel = 0;
	break;
    case straightRightNonTopCollision:
	paddleOne.x = FPMAKE(344-paddleTwo.width,0);
	paddleTwo.y = FPMAKE(100,0);
	paddleTwo.yVel = 0;
	paddleTwo.xVel = MIN_PADDLE_SPEED_X;
	
	ball.x = FPMAKE(334-ball.width,0);
	ball.y = FPMAKE(100-DEFAULT_BALL_HEIGHT+1, 0);
	ball.xVel = MAX_BALL_SPEED_X;
	ball.yVel = 0;
	break;
    case straightRightPaddleTopCollision:
	paddleTwo.x = FPMAKE(280,0);
	paddleTwo.y = FPMAKE(110, 0);
	paddleTwo.xVel = FPMAKE(0,0);
	paddleTwo.yVel = FPMAKE(-1,0);

	paddleOne.x = FPMAKE(35,0);
	paddleOne.y = FPMAKE(110,0);

	ball.x = FPMAKE(270,0);
	ball.y = FPMAKE(100-DEFAULT_BALL_HEIGHT-8,0);
	ball.xVel = FPMAKE(1,0);
	ball.yVel = FPMAKE(0,0);


	setBallXVel(FPMAKE(0, 8), &ball);
	
	break;

    case straightRightPaddleBottomCollision:
	paddleTwo.x = FPMAKE(280,0);
	paddleTwo.y = FPMAKE(90,0);
	paddleTwo.xVel = FPMAKE(0,0);
	paddleTwo.yVel = FPMAKE(1,0);
	
	paddleOne.x = FPMAKE(35,0);
	paddleOne.y = FPMAKE(90,0);

	ball.x = FPMAKE(270,0);
	ball.y = FPMAKE(100+DEFAULT_PADDLE_HEIGHT+8,0);
	ball.xVel = FPMAKE(1,0);
	ball.yVel = FPMAKE(0,0);

	setBallXVel(FPMAKE(0, 8), &ball);
	
	break;

    case straightRightPaddleRearCollision:
	paddleOne.x = FPMAKE(DEFAULT_LEFT_ACCAREA_X + DEFAULT_LEFT_ACCAREA_WIDTH - DEFAULT_PADDLE_WIDTH, 0);
	paddleOne.y = FPMAKE(100,0);
	ball.x = FPMAKE(FPINT(paddleOne.x) - DEFAULT_BALL_WIDTH - 5, 0);
	ball.y = FPMAKE(100,0);
	setBallXVel(-1*FPMAKE(0, 6), &ball);
	setPaddleXVel(FPMAKE(-1,0), &paddleOne);

     	break;
    case straightLeftPaddleRearCollision:
	paddleTwo.x = FPMAKE(DEFAULT_RIGHT_ACCAREA_X, 0);
	paddleTwo.y = FPMAKE(100,0);
	ball.x = FPMAKE(FPINT(paddleTwo.x) + DEFAULT_BALL_WIDTH + 5, 0);
	ball.y = FPMAKE(100,0);
	setBallXVel(FPMAKE(0, 6), &ball);
	setPaddleXVel(FPMAKE(1,0), &paddleTwo);
	break;

    case noStartState:
	gPngGame.isPlayerOneHuman = 1;
	gPngGame.isPlayerTwoHuman = 0;
	break;
    default:
	printf("default - please provide a value");
	break;
    }

    assembleDefaultPongGame();
 }


#endif

