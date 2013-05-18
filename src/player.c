#include "player.h"
#include "gPngStructPrint.h"

void playerOneInput(GPngGame *gPngGame)
{
    if(gPngGame->paddleOne->y < gPngGame->ball->y) {
	setPaddleXVel(gPngGame->paddleOne->xVel + PLAYER_INPUT_STEP, gPngGame->paddleOne);
    } else {
	setPaddleXVel(gPngGame->paddleTwo->xVel - PLAYER_INPUT_STEP, gPngGame->paddleOne);
    }
}

void playerTwoInput(GPngGame *gPngGame)
{
    // y
    if(gPngGame->paddleTwo->y < gPngGame->ball->y) {
	setPaddleYVel(gPngGame->paddleTwo->yVel + PLAYER_INPUT_STEP, gPngGame->paddleTwo);
    } else {
	setPaddleYVel(gPngGame->paddleTwo->yVel - PLAYER_INPUT_STEP, gPngGame->paddleTwo);
    }
    // x
    if(gPngGame->ball->xVel < 0) { //ball moving away
	// check if we are already moving in the right direction
	if(gPngGame->paddleTwo->xVel > 0) {
	    // we don't have to do anything
	} else {
	    // simulate a joystick event in the correct direction
	    setPaddleXVel(gPngGame->paddleTwo->xVel + PLAYER_INPUT_STEP, gPngGame->paddleTwo);
	}
    } else { // the ball is moving towards the paddle
	// check if the ball has passed the accarea 
	if(FPINT(gPngGame->ball->x) > DEFAULT_RIGHT_ACCAREA_X) {
	    setPaddleXVel(gPngGame->paddleTwo->xVel - PLAYER_INPUT_STEP, gPngGame->paddleTwo);
	} else {
	    // we wait until the ball is closer
	}
    }
}

void realPlayerOneInput(GPngGame *gPngGame)
{
    char joystickEvent;
    volatile char *dataPortA = (char*) 0xdc00;
    joystickEvent = *(dataPortA);
    
    if (!(joystickEvent & 1)) {	//pressedUp
	setPaddleYVel(gPngGame->paddleOne->yVel - PLAYER_INPUT_STEP, gPngGame->paddleOne);
    } else if (!(joystickEvent & 2)) {	//pressed down
	setPaddleYVel(gPngGame->paddleOne->yVel + PLAYER_INPUT_STEP, gPngGame->paddleOne);
    } else if(!(joystickEvent & 4)) {
	setPaddleXVel(gPngGame->paddleOne->xVel - PLAYER_INPUT_STEP, gPngGame->paddleOne);
    } else if(!(joystickEvent & 8)) {
	setPaddleXVel(gPngGame->paddleOne->xVel + PLAYER_INPUT_STEP, gPngGame->paddleOne);
    } else if (!(joystickEvent & 16)) {
	
    }
}

void realPlayerTwoInput(GPngGame *gPngGame)
{
    
    char joystickEvent;
    char *dataPortB = (char*) 0xdc01;

    joystickEvent = *(dataPortB);
    
    if (!(joystickEvent & 1)) {	//pressedUp
	setPaddleYVel(gPngGame->paddleTwo->yVel - PLAYER_INPUT_STEP, gPngGame->paddleTwo);
    } else if (!(joystickEvent & 2)) {	//pressed down
	setPaddleYVel(gPngGame->paddleTwo->yVel + PLAYER_INPUT_STEP, gPngGame->paddleTwo);
    } else if(!(joystickEvent & 4)) {
	setPaddleXVel(gPngGame->paddleTwo->xVel - PLAYER_INPUT_STEP, gPngGame->paddleTwo);
    } else if(!(joystickEvent & 8)) {
	setPaddleXVel(gPngGame->paddleTwo->xVel + PLAYER_INPUT_STEP, gPngGame->paddleTwo);
    } else if (!(joystickEvent & 16)) {
	
    }

}
