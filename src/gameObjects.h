#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include "gPngMath.h"
#include "gamePhysicsStructs.h"

#define SCREEN_WIDTH (320)
#define SCREEN_HEIGHT (200)
#define SCREEN_START_X (24)
#define SCREEN_START_Y (50)

#define DEFAULT_PADDLE_HEIGHT (21)
#define DEFAULT_PADDLE_WIDTH (5)
#define DEFAULT_COURT_WIDTH (SCREEN_WIDTH)
#define DEFAULT_COURT_HEIGHT (SCREEN_HEIGHT)
#define DEFAULT_RIGHT_ACCAREA_WIDTH (64)
#define DEFAULT_LEFT_ACCAREA_X (SCREEN_START_X)
#define DEFAULT_LEFT_ACCAREA_WIDTH (64)
#define DEFAULT_RIGHT_ACCAREA_X (SCREEN_START_X + DEFAULT_COURT_WIDTH-DEFAULT_RIGHT_ACCAREA_WIDTH)
#define DEFAULT_BALL_HEIGHT (7)
#define DEFAULT_BALL_WIDTH (7)
#define PADDLE_COLLISION_DISABLE_TIME (30)
#define DEFAULT_BALL_WEIGHT (1)
#define DEFAULT_PADDLE_WEIGHT (0)


// x and y are measured from the top left corner
typedef struct PADDLE
{
    GPINT x;
    GPINT y;

    GPINT xVel;
    GPINT yVel;

    GPINT height;
    GPINT width;
    int disabledCounter;
    unsigned char weight;
}Paddle;

typedef struct BALL
{
    GPINT x;
    GPINT y;

    GPINT xVel;
    GPINT yVel;

    GPINT height;
    GPINT width;
    int disabledCounter;
    unsigned char weight;
}Ball;

typedef struct COURT{
    GPINT width;
    GPINT height;

    GPINT x;
    GPINT y;

    GPINT leftAccAreaX;
    GPINT leftAccAreaWidth;

    GPINT rightAccAreaX;
    GPINT rightAccAreaWidth;
}Court;

typedef struct PONGGAME {
    Paddle *paddleOne;
    Paddle *paddleTwo;
    Ball *ball;
    Court *court;
    
    GPINT epsilon;
    GPINT gravity;
    char useGravity;
    
    //score
    int pointsPlayerOne;
    int pointsPlayerTwo;
    
    int isPlayerOneHuman;
    int isPlayerTwoHuman;

    unsigned int hitCounter;

    GravityDirection gravityDirection;
    GPINT xGravity;
    GPINT yGravity;

} GPngGame;

typedef enum PLAYERINPUT {
	NO_INPUT = 0,
	NORTH = 1,
	NORTH_EAST = 2,
	EAST = 3,
	SOUTH_EAST = 4,
	SOUTH = 5,
	SOUTH_WEST = 6,
	WEST = 7,
	NORTH_WEST = 8
} PlayerInput;

void initDefaultPaddleOne(Paddle *paddle1);
void initDefaultPaddleTwo(Paddle *paddle2);
void initDefaultBall(Ball *ball);
void initDefaultCourt(Court *court);

//setters
void setBallXVel(GPINT x, Ball *ball);
void setBallYVel(GPINT y, Ball *ball);
void setPaddleXVel(GPINT x, Paddle *paddle);
void setPaddleYVel(GPINT y, Paddle *paddle);
void mirrorBallXVel(Ball *ball);
void mirrorBallYVel(Ball *ball);
void mirrorPaddleXVel(Paddle *paddle);
void mirrorPaddleYVel(Paddle *paddle);
#endif
