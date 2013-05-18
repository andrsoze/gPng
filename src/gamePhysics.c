#include "gamePhysics.h"
#include <stdlib.h>
#include <time.h>

static int firstTimeRandom = 1;
GravityDirection randomGravityDirection() {
    int randomNumber;
    if(firstTimeRandom) {
	srand(time(NULL));
	firstTimeRandom = 0;
    }
    
    randomNumber = rand() % 9;
    return (GravityDirection)randomNumber;
}

const GPINT gravityStepPositive = FPMAKE(0,1);
const GPINT gravityStepNegative = -1 * FPMAKE(0,1);
void updateGravity(GPngGame *gPngGame) {
    switch(gPngGame->gravityDirection) {
    case noGravity:
	gPngGame->xGravity = 0;
	gPngGame->yGravity = 0;
	break;
    case northGravity:
	gPngGame->xGravity = 0;
	gPngGame->yGravity = gravityStepNegative;
	break;
    case northEastGravity:
	gPngGame->xGravity = gravityStepPositive;
	gPngGame->yGravity = gravityStepNegative;
	break;
    case eastGravity:
	gPngGame->xGravity = gravityStepPositive;
	gPngGame->yGravity = 0;
	break;
    case southEastGravity:
	gPngGame->xGravity = gravityStepPositive;
	gPngGame->yGravity = gravityStepPositive;
	break;
    case southGravity:
	gPngGame->xGravity = 0;
	gPngGame->yGravity = gravityStepPositive;
	break;
    case southWestGravity:
	gPngGame->xGravity = gravityStepNegative;
	gPngGame->yGravity = gravityStepPositive;
	break;
    case westGravity:
	gPngGame->xGravity = gravityStepNegative;
	gPngGame->yGravity = 0;
	break;
    case northWestGravity:
	gPngGame->xGravity = gravityStepNegative;
	gPngGame->yGravity = gravityStepNegative;
	break;
    }
}


void applyGravity(GPngGame *gPngGame, unsigned char gravityCounter) {
    unsigned char baseWeight, currentWeight;
    
    baseWeight = 16;

    //ball
    currentWeight = baseWeight << gPngGame->ball->weight;
    if(!(gravityCounter % currentWeight)) {
	setBallXVel(gPngGame->ball->xVel + gPngGame->xGravity, gPngGame->ball);
	setBallYVel(gPngGame->ball->yVel + gPngGame->yGravity, gPngGame->ball);
    }
    
    //paddle one
    currentWeight = baseWeight << gPngGame->paddleOne->weight;
    if(!(gravityCounter % currentWeight)) {
	setPaddleXVel(gPngGame->paddleOne->xVel + gPngGame->xGravity, gPngGame->paddleOne);
	setPaddleYVel(gPngGame->paddleOne->yVel + gPngGame->yGravity, gPngGame->paddleOne);
    }

    //paddle two
    currentWeight = baseWeight << gPngGame->paddleTwo->weight;
    if(!(gravityCounter % currentWeight)) {
	setPaddleXVel(gPngGame->paddleTwo->xVel + gPngGame->xGravity, gPngGame->paddleTwo);
	setPaddleYVel(gPngGame->paddleTwo->yVel + gPngGame->yGravity, gPngGame->paddleTwo);
    }
}

CollisionDirection collidePaddleOneWithCourt(Paddle *paddle1, Court *court)
{
    int n;
    int s;
    int e;
    int w;
    
    n = s = w = e = 0;
        
    // y
    if(paddle1->y < court->y) {
	paddle1->y = court->y;
	paddle1->yVel = FPMUL(paddle1->yVel, COURT_PADDLE_BOUNCINESS);
	mirrorPaddleYVel(paddle1);
	n = 1;
	
    } // paddle above court end
    else if((paddle1->y + paddle1->height) > (court->y + court->height)) {
	paddle1->y = (court->height + court->y - paddle1->height);
	paddle1->yVel = FPMUL(paddle1->yVel, COURT_PADDLE_BOUNCINESS);
	mirrorPaddleYVel(paddle1);
	s = 1;
    }
    
    // x
    if(paddle1->x < court->x) {
	paddle1->x = court->x;
	paddle1->xVel = FPMUL(paddle1->xVel, COURT_PADDLE_BOUNCINESS);
	mirrorPaddleXVel(paddle1);
	w = 1;
    } else if((paddle1->x + paddle1->width) > (court->leftAccAreaWidth+court->x)) {
	paddle1->x = (court->leftAccAreaWidth + court->x - paddle1->width);
	paddle1->xVel = 0;
	e = 1;
    }
    
    return convertDirections(n, s, e, w);
}

CollisionDirection collidePaddleTwoWithCourt(Paddle *paddle2, Court *court)
{
    int n;
    int s;
    int e;
    int w;

    n = s = w = e = 0;

    //y
    if(paddle2->y < court->y) {
	paddle2->y = court->y;
	paddle2->yVel = FPMUL(paddle2->yVel, COURT_PADDLE_BOUNCINESS);
	mirrorPaddleYVel(paddle2);
	n = 1;
    } //paddle above court end
    else if(paddle2->y + paddle2->height > court->y + court->height) {
	paddle2->y = (court->height + court->y - paddle2->height);
	paddle2->yVel = FPMUL(paddle2->yVel, COURT_PADDLE_BOUNCINESS);
	mirrorPaddleYVel(paddle2);
	s = 1;
    }

    //x
    if(paddle2->x < court->rightAccAreaX) {
	paddle2->x = court->rightAccAreaX;
	paddle2->xVel = 0;
	w = 1;
    } else if((paddle2->x + paddle2->width) > (court->rightAccAreaX + court->rightAccAreaWidth)) {
	paddle2->x = (court->rightAccAreaX + court->rightAccAreaWidth - paddle2->width);
	paddle2->xVel = FPMUL(paddle2->xVel, COURT_PADDLE_BOUNCINESS);
	mirrorPaddleXVel(paddle2);
	e = 1;
    }

    return convertDirections(n, s, e, w);
}

CollisionDirection convertDirections(int n, int s, int e, int w)
{
    if(n) {
	if(e) {
	    return nECollision;
	} else if(w) {
	    return nWCollision;
	} else {
	    return nCollision;
	}
    } else if(s) {
	if(e) {
	    return sECollision;
	} else if (w) {
	    return sWCollision;
	} else {
	    return sCollision;
	}

    }  else {
	if(w) {
	    return wCollision;
	} else if(e) {
	    return eCollision;
	}
    }
    return noCollision;
}

void updateBall(Ball *ball, GPINT friction)
{
#ifdef USE_FRICTION
    //apply friction
    setBallXVel(FPMUL(ball->xVel, friction), ball);
    setBallYVel(FPMUL(ball->yVel, friction), ball);
#else
    friction = friction;
#endif

    // update positions
    ball->x += ball->xVel;
    ball->y += ball->yVel;
}

void updatePaddle(Paddle *paddle, GPINT friction)
{
    //update position
    paddle->x += paddle->xVel;
    paddle->y += paddle->yVel;
#ifdef USE_FRICTION
    //apply friction
    paddle->xVel = FPMUL(paddle->xVel, friction);
    paddle->yVel = FPMUL(paddle->yVel, friction);
#else 
    friction = friction;
#endif
}
