#ifndef GAME_PHYSICS_BALL
#define GAME_PHYSICS_BALL

#include "gameObjects.h"
#include "gamePhysics.h"
#include <stdio.h>

typedef enum BALL_PADDLE_COLLISION_TYPE {
    topCollision = 0,
    bottomCollision,
    frontCollision,
    rearCollision
} BallPaddleCollisionType;


CollisionDirection collideBallWithCourt(Ball *ball, Court *court);
unsigned char collideBallWithPaddleOne(Ball *ball, Paddle *paddle1, GPINT epsilon);
unsigned char collideBallWithPaddleTwo(Ball *ball, Paddle *paddle2, GPINT epsilon);
void handleBallCollisionWithPaddle(Ball *ball, Paddle *paddle, int isPaddleOne, BallPaddleCollisionType collisionType, GPINT epsilon);
void handleBallCollision(Ball *ball, Court *court, CollisionDirection cd);



#endif
