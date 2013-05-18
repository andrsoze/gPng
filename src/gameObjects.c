#include "gameObjects.h"
#include "gamePhysicsStructs.h"
#include <stdio.h>

void initDefaultPaddleTwo(Paddle *paddle2)
{
    paddle2->x = FPMAKE(DEFAULT_RIGHT_ACCAREA_X,0);
    paddle2->y = FPMAKE(DEFAULT_COURT_HEIGHT/2,0);

    paddle2->xVel = FPMAKE(0,0);
    paddle2->yVel = FPMAKE(0,0);

    paddle2->height = FPMAKE(DEFAULT_PADDLE_HEIGHT,0);
    paddle2->width = FPMAKE(DEFAULT_PADDLE_WIDTH,0);
}

void initDefaultPaddleOne(Paddle *paddle1)
{
    paddle1->x = FPMAKE(DEFAULT_LEFT_ACCAREA_WIDTH,0);
    paddle1->y = FPMAKE(DEFAULT_COURT_HEIGHT/2,0);
    
    paddle1->xVel = FPMAKE(0,0);
    paddle1->yVel = FPMAKE(0,0);
    
    paddle1->height = FPMAKE(DEFAULT_PADDLE_HEIGHT,0);
    paddle1->width = FPMAKE(DEFAULT_PADDLE_WIDTH,0);
}

void initDefaultCourt(Court *court)
{
    court->width = FPMAKE(DEFAULT_COURT_WIDTH,0);
    court->height = FPMAKE(DEFAULT_COURT_HEIGHT,0);
    court->x = FPMAKE(SCREEN_START_X, 0);
    court->y = FPMAKE(SCREEN_START_Y, 0);
    
    court->leftAccAreaWidth = FPMAKE(DEFAULT_LEFT_ACCAREA_WIDTH,0);
    court->leftAccAreaX = FPMAKE(DEFAULT_LEFT_ACCAREA_X,0);
    court->rightAccAreaWidth = FPMAKE(DEFAULT_RIGHT_ACCAREA_WIDTH,0);
    court->rightAccAreaX = FPMAKE(DEFAULT_RIGHT_ACCAREA_X,0);
}

void initDefaultBall(Ball *ball)
{
    ball->x = FPMAKE((DEFAULT_COURT_WIDTH/2 - DEFAULT_BALL_WIDTH/2),0);
    ball->y = FPMAKE((DEFAULT_COURT_HEIGHT/2 - DEFAULT_BALL_HEIGHT/2),0);
    
    ball->xVel = 0;
    ball->yVel = 0;

    ball->height = FPMAKE(DEFAULT_BALL_HEIGHT,0);
    ball->width = FPMAKE(DEFAULT_BALL_WIDTH,0);
}

void setBallXVel(GPINT newXVel, Ball *ball) {
    if(newXVel > MAX_BALL_SPEED_X) {
	ball->xVel = MAX_BALL_SPEED_X;
    } else if(newXVel < MIN_BALL_SPEED_X) {
	ball->xVel = MIN_BALL_SPEED_X;
    } else {
	ball->xVel = newXVel;
    }
}

void setBallYVel(GPINT newYVel, Ball *ball) {

    if(newYVel > MAX_BALL_SPEED_Y) {
	ball->yVel = MAX_BALL_SPEED_Y;
    } else if(newYVel < MIN_BALL_SPEED_Y) {
	ball->yVel = MIN_BALL_SPEED_Y;
    } else {
	ball->yVel = newYVel;
    }
}

void mirrorBallXVel(Ball *ball) {
    ball->xVel *= -1;
}

void mirrorBallYVel(Ball *ball) {
    ball->yVel *= -1;
}

void mirrorPaddleXVel(Paddle *paddle) {
    paddle->xVel *= -1;
}

void mirrorPaddleYVel(Paddle *paddle) {
    paddle->yVel *= -1;
}

void setPaddleXVel(GPINT newXVel, Paddle *paddle) {
    if(newXVel > MAX_PADDLE_SPEED_X) {
	paddle->xVel = MAX_PADDLE_SPEED_X;
    } else if(newXVel < MIN_PADDLE_SPEED_X) {
	paddle->xVel = MIN_PADDLE_SPEED_X;
    } else {
	paddle->xVel = newXVel;
    }
}

void setPaddleYVel(GPINT newYVel, Paddle *paddle) {
    if(newYVel > MAX_PADDLE_SPEED_Y) {
	paddle->yVel = MAX_PADDLE_SPEED_Y;
    } else if(newYVel < MIN_PADDLE_SPEED_Y) {
	paddle->yVel = MIN_PADDLE_SPEED_Y;
    } else {
	paddle->yVel = newYVel;
    }
}



