#include <stdlib.h>
#include "gPngGame.h"
#include "gamePhysicsStructs.h"
#include "gPngStructPrint.h"
#include "gamePhysics.h"
#include <time.h>
#include <assert.h>
#include "player.h"
#include "cmdString.h"
#ifdef TARGET_C64
#include "gPngGraphics.h"
#endif

/*
 - update(input, gameEntities)
 - check ballPaddle1Collision
 - check ballPaddle2Collision
 - check ballCourtCollision
 - check paddle1CourtCollision
 - check paddle2CourtCollision
 
 - apply gravity
 - update positions(ball, paddle1, paddle2, court)
 *
 */

void randomBall(Ball *ball);
void updateToRandomGravity(GPngGame *gPngGame);

void resetPongGame(GPngGame *gPngGame)
{
    gPngGame->paddleOne->x = FPMAKE(DEFAULT_LEFT_ACCAREA_X, 0);
    gPngGame->paddleOne->y = FPMAKE(SCREEN_START_Y + (SCREEN_HEIGHT/2), 0);
    gPngGame->paddleOne->xVel = 0;
    gPngGame->paddleOne->yVel = 0;
    gPngGame->paddleOne->weight = DEFAULT_PADDLE_WEIGHT;
    
    gPngGame->paddleTwo->x = FPMAKE(DEFAULT_RIGHT_ACCAREA_X, 0);
    gPngGame->paddleTwo->y = FPMAKE(SCREEN_START_Y + (SCREEN_HEIGHT/2), 0);
    gPngGame->paddleTwo->xVel = 0;
    gPngGame->paddleTwo->yVel = 0;
    gPngGame->paddleTwo->weight = DEFAULT_PADDLE_WEIGHT;
    
    gPngGame->ball->x = FPMAKE(SCREEN_START_X + (SCREEN_WIDTH/2), 0);
    gPngGame->ball->y = FPMAKE(SCREEN_START_Y + (SCREEN_HEIGHT/2), 0);
    
    gPngGame->ball->weight = DEFAULT_BALL_WEIGHT;
    randomBall(gPngGame->ball);
    
    gPngGame->hitCounter = 0;
    updateToRandomGravity(gPngGame);
}

void updateToRandomGravity(GPngGame *gPngGame) {
    gPngGame->gravityDirection = randomGravityDirection();
    updateGravity(gPngGame);
    fillArrowSpriteMem(gPngGame->gravityDirection);
}


void randomBall(Ball *ball)
{
    static int firstRandomBallUse = 1;
    int r1, r2;
    if(firstRandomBallUse) {
        srand(time(NULL));
        firstRandomBallUse = 0;
    }
    
    r1 = (rand() > RAND_MAX/2);
    r2 = (rand() > RAND_MAX/2);
    
    setBallXVel((r1)?MAX_INITIAL_BALL_SPEED_X:MIN_INITIAL_BALL_SPEED_X, ball);
    setBallYVel((r2)?MAX_INITIAL_BALL_SPEED_Y:MIN_INITIAL_BALL_SPEED_Y, ball);
}

void gameUpdate(GPngGame *gPngGame) {
    GravPngScoreChange scoreChange;
    
    scoreChange = updatePongGame(gPngGame);
    switch(scoreChange) {
        case PLAYER_ONE_GOAL:
            gPngGame->pointsPlayerOne++;
            break;
        case PLAYER_TWO_GOAL:
            gPngGame->pointsPlayerTwo++;
            break;
        case NO_GOAL:
            break;
    }
    
    if(scoreChange == PLAYER_ONE_GOAL || scoreChange == PLAYER_TWO_GOAL) {
        flashScreen();
    }
}

GPngState gameChangeState(GPngGame * gPngGame) {
    assert(gPngGame->isPlayerOneHuman);
    
    if(gPngGame->pointsPlayerOne >= FINAL_GAME_SCORE) {
        displayWinner(1);
        return MENU_STATE;
    } else if (gPngGame->pointsPlayerTwo >= FINAL_GAME_SCORE) {
        displayWinner(0);
        return MENU_STATE;
    } else {
        return (gPngGame->isPlayerTwoHuman)?GAME_STATE_SINGLE:GAME_STATE_DOUBLE;
    }
}

static unsigned char gravityCounter = 1;
GravPngScoreChange updatePongGame(GPngGame *gPngGame)
{
    char *hwCollision;
    CollisionDirection ballCourt;
    //#define DEBUG_LOG
#ifdef DEBUG_LOG
    static FILE *file;
    if(!file) {
        file = fopen("gPngGameStatePrint.txt", "w");
    }
    printPaddleToStream(file, gPngGame->paddleOne);
    printPaddleToStream(file, gPngGame->paddleTwo);
    printBallToStream(file, gPngGame->ball);
    printBigFooterToStream(file);
    
#endif
    
    collidePaddleOneWithCourt(gPngGame->paddleOne, gPngGame->court);
    collidePaddleTwoWithCourt(gPngGame->paddleTwo, gPngGame->court);
    
    ballCourt = collideBallWithCourt(gPngGame->ball, gPngGame->court);
    
#ifdef TARGET_C64
    //optimize by checking the hardware register if there was a sprite collision involving the ball
    //NB the ball sprite is hard coded to sprite no 0 in here and in gravpngGraphics.c
    hwCollision = (char*)0xd01e;
    if((*hwCollision) & 0x1) {
        gPngGame->hitCounter += collideBallWithPaddleOne(gPngGame->ball, gPngGame->paddleOne, gPngGame->epsilon);
        gPngGame->hitCounter += collideBallWithPaddleTwo(gPngGame->ball, gPngGame->paddleTwo, gPngGame->epsilon);
        //	printf("gPngGame->hitCounter %d\n", gPngGame->hitCounter);
    }
#else
    
    gPngGame->hitCounter += collideBallWithPaddleOne(gPngGame->ball, gPngGame->paddleOne, gPngGame->epsilon);
    gPngGame->hitCounter += collideBallWithPaddleTwo(gPngGame->ball, gPngGame->paddleTwo, gPngGame->epsilon);
#endif
    
    //apply gravity
    applyGravity(gPngGame, ++gravityCounter);
    updatePongGamePositions(gPngGame->ball, gPngGame->paddleOne, gPngGame->paddleTwo);
    
    //update gravity if needed
    if(gPngGame->hitCounter == 3) {
        gPngGame->hitCounter = 0;
        updateToRandomGravity(gPngGame);
    }
    
    if (ballCourt == eCollision || ballCourt == sECollision || ballCourt == nECollision) {
        gPngGame->pointsPlayerOne++;
        return PLAYER_ONE_GOAL;
    }else if(ballCourt == wCollision || ballCourt == sWCollision || ballCourt == nWCollision) {
        gPngGame->pointsPlayerTwo++;
        return PLAYER_TWO_GOAL;
    } else {
        return NO_GOAL;
    }
    
}

void updatePongGamePositions(Ball *ball, Paddle *paddleOne, Paddle *paddleTwo)
{
#ifdef TARGET_C64
    static GPINT sFriction = FPMAKE(1,0);
#else
    static GPINT sFriction = 0x10000;
#endif
    
    updateBall(ball, sFriction);
    updatePaddle(paddleOne, sFriction);
    
    updatePaddle(paddleTwo, sFriction);
}

void gameDisplayInit() {
	char *pokePtr;
	pokePtr = (char*)53280l;
	(*pokePtr) = 0;
	pokePtr = (char*)53281l;
	(*pokePtr) = 11;
	
    clearScreen();
    setupSpriteMemPtrs();
    fillSpriteMem();
    
}

void gameClean() {
    printf("gameClean not implemented\n");
}

void handlePlayerInput(GPngGame *gPngGame, int isPlayerOne) {
    
    Paddle *paddleInUse;
    if(isPlayerOne) {
        paddleInUse = gPngGame->paddleOne;
    } else {
        paddleInUse = gPngGame->paddleTwo;
    }
    
    if(paddleInUse->disabledCounter) {
        paddleInUse->disabledCounter--;
    } else {
        if(isPlayerOne) {
            if(gPngGame->isPlayerOneHuman) {
                realPlayerOneInput(gPngGame);
            } else {
                playerOneInput(gPngGame);
            }
        } else {
            if(gPngGame->isPlayerTwoHuman) {
                realPlayerTwoInput(gPngGame);
            } else {
                playerTwoInput(gPngGame);
            }
        }
    }
}

void gameRenderGame(GPngGame *gPngGame) {
    drawBall(gPngGame->ball);
    drawPaddleSprites(gPngGame->paddleOne, gPngGame->paddleTwo);
    drawArrow();
}
