#ifndef GAME_PHYSICS
#define GAME_PHYSICS
#include "gamePhysicsStructs.h"
#include "gameObjects.h"
#include "gamePhysicsBall.h"
#include <stdio.h>

CollisionDirection collidePaddleOneWithCourt(Paddle *paddle1, Court *court);
CollisionDirection collidePaddleTwoWithCourt(Paddle *paddle2, Court *court);
CollisionDirection collideBallWithCourt(Ball *ball, Court *court);
CollisionDirection convertDirections(int n, int s, int e, int w);

void applyGravity(GPngGame *gPngGame, unsigned char gravityCounter);
void updateGravity(GPngGame *gPngGame);
GravityDirection randomGravityDirection();
void updateBall(Ball *ball, GPINT friction);
void updatePaddle(Paddle *paddle, GPINT friction);
void updatePaddleOne(Paddle *paddle1);
void updatePaddleTwo(Paddle *paddle2);
// TODO: timestep is ignored for now
void updatePostions(Ball *ball, Paddle *paddleOne, Paddle *paddleTwo, GPINT timeStep);
#endif


