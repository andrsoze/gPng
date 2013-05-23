#include "gamePhysics.h"
#include "gPngStructPrint.h"
#include <assert.h>
#include <stdlib.h>
/*
 CollisionDirection collideBallWithCourt(Ball *ball, Court *court)
 {
 //check collisions with the sides of the court
 //in the order of west, east, north, south
 //if there is a west or east collision, return
 //the goal result for each player respectively
 int n,s,w,e;
 
 n = s = w = e = 0;
 
 //west & east
 if(ball->x < 0) {
 w = 1;
 } else if((ball->x+ball->width) > court->width) {
 e = 1;
 }
 
 //north & south
 if(ball->y < 0) {
 n = 1;
 } else if((ball->y + ball->height) > court->height) {
 s = 1;
 }
 
 return convertDirections(n, s, e, w);
 }
 */
int isBottomCollision( Ball *ball, Paddle *paddle);
int isTopCollision(Ball *ball, Paddle *paddle);

CollisionDirection collideBallWithCourt(Ball *ball, Court *court) {
    int n, s, e	, w;
    CollisionDirection cd;
    n = s = w = e = 0;
    
    //printBall(ball);
    
    //y
    if (ball->y < court->y) {
        n = 1;
    } else if ((ball->y + ball->height) > (court->height + court->y)) {
        //	printBall(ball);
        //	printCourt(court);
        s = 1;
    }
    
    //x
    if (ball->x < court->x) {
        w = 1;
    } else if ((ball->x + ball->width) > court->width + court->x) {
        e = 1;
    }
    
#ifndef NO_DEBUG_PRINT
#endif
    cd = convertDirections(n, s, e, w);
    handleBallCollision(ball, court, cd);
    return cd;
}

unsigned char collideBallWithPaddleOne(Ball *ball, Paddle *paddle1, GPINT epsilon) {
    // start out by checking if ball is "inside" the paddle
    // in the west - east direction
    // if so check the north-south axis as well
    
    if (ball->x < (paddle1->x + paddle1->width)
        && (ball->x + ball->width) > paddle1->x) {
        
        // x-axis collision confirmed
        // check y-axis
        if ((ball->y + ball->height) > paddle1->y
            && ball->y < (paddle1->y + paddle1->height)) {
            // collision established
            
            //check the special case of rear collision
            if(ball->xVel < 0 && paddle1->xVel < 0) {
                //both going left
                if(abs(ball->xVel) < abs(paddle1->xVel)) {
                    // paddle has greater vel, heuristic: rear collision
                    handleBallCollisionWithPaddle(ball, paddle1, 1, rearCollision, epsilon);
                    return 1;
                }
            }
            
            // check the special case of top of a paddle collision
            if(ball->x < paddle1->x + paddle1->width - MAX_BALL_SPEED_X - MAX_PADDLE_SPEED_X)
            {
                //approx good enough x for a top collision
                //check if same goes for y
                if(ball->y+ball->height < paddle1->y + MAX_BALL_SPEED_Y) {
                    if(isTopCollision(ball, paddle1)) {
                        handleBallCollisionWithPaddle(ball, paddle1, 1, topCollision, epsilon);
                        return 1;
                    }
                } else if(ball->y+ball->height > paddle1->y + paddle1->height - MAX_BALL_SPEED_Y) {
                    if(isBottomCollision(ball, paddle1)) {
                        handleBallCollisionWithPaddle(ball, paddle1, 0, bottomCollision, epsilon);
                        return 1;
                    }
                }
            }
            handleBallCollisionWithPaddle(ball, paddle1, 1, frontCollision, epsilon);
            return 1;
        }
    }
    return 0;
}

unsigned char collideBallWithPaddleTwo(Ball *ball, Paddle *paddle2, GPINT epsilon) {
    // start out by checking if ball is "inside" the paddle
    // in the west - east direction
    // if so check the north-south axis as well
    if ((ball->x + ball->width) > paddle2->x
        && ball->x < paddle2->x+paddle2->width) {
        // x-axis collision confirmed
        // check y-axis
        if ((ball->y + ball->height) > paddle2->y
            && ball->y < (paddle2->y + paddle2->height)) {
            // collision established
            
            //check the special case of rear collision
            if(ball->xVel > 0 && paddle2->xVel > 0) {
                // both going right
                
                if(ball->xVel < paddle2->xVel) {
                    // paddle has greater vel than ball, heuristic: rear collision
                    handleBallCollisionWithPaddle(ball, paddle2, 0, rearCollision, epsilon);
                    return 1;
                }
            }
            // check the special case of top of a top of paddle collision
            if(ball->x + ball->width > paddle2->x + MAX_BALL_SPEED_X + MAX_PADDLE_SPEED_X) {
                //approx good enough x for a top collision
                //check if same goes for y
                if(ball->y+ball->height < paddle2->y + MAX_BALL_SPEED_Y) {
                    if(isTopCollision(ball, paddle2)) {
                        handleBallCollisionWithPaddle(ball, paddle2, 0, topCollision, epsilon);
                        return 1;
                    }
                } else if(ball->y+ball->height > paddle2->y + paddle2->height - MAX_BALL_SPEED_Y) {
                    if(isBottomCollision(ball, paddle2)) {
                        handleBallCollisionWithPaddle(ball, paddle2, 0, bottomCollision, epsilon);
                        return 1;
                    }
                }
                
                handleBallCollisionWithPaddle(ball, paddle2, 0, frontCollision, epsilon);
                return 1;
            }
        }
    }
    return 0;
}

int isTopCollision(Ball *ball, Paddle *paddle) {
    if(ball->yVel < 0 && paddle->yVel < 0) {
        return (ball->yVel > paddle->yVel);
    } else if(ball->yVel > 0 && paddle->yVel < 0) {
        return 1;
    } else if(ball->yVel < 0 && paddle->yVel < 0) {
        return (paddle->yVel > ball->yVel);
    } else {
        return 0;
    }
}

int isBottomCollision( Ball *ball, Paddle *paddle) {
    if(ball->yVel < 0 && paddle->yVel > 0) {
        return 1;
    } else if(ball->yVel > 0 && paddle->yVel > 0) {
        return (ball->yVel < paddle->yVel);
    } else if(ball->yVel < 0 && paddle->yVel < 0) {
        return (ball->yVel > paddle->yVel);
    } else {
        return 0;
    }
}

void bouncePaddleFromBallCollision(Paddle *paddle, BallPaddleCollisionType collisionType)
{
    switch(collisionType) {
        case frontCollision:
            setPaddleXVel(FPMUL(paddle->xVel, PADDLE_BOUNCINESS), paddle);
            mirrorPaddleXVel(paddle);
            break;
        case rearCollision:
            setPaddleXVel(FPMUL(paddle->xVel, PADDLE_BOUNCINESS), paddle);
            mirrorPaddleXVel(paddle);
            break;
        case topCollision:
            setPaddleYVel(FPMUL(paddle->yVel, PADDLE_BOUNCINESS), paddle);
            mirrorPaddleYVel(paddle);
            break;
        case bottomCollision:
            setPaddleYVel(FPMUL(paddle->yVel, PADDLE_BOUNCINESS), paddle);
            mirrorPaddleYVel(paddle);
            break;
    }
    
}

void handleBallCollisionWithPaddle(Ball *ball, Paddle *paddle, int isPaddleOne, BallPaddleCollisionType collisionType, GPINT epsilon)
{
    GPINT initialBallXVel, initialBallYVel;
    //printf("collisionType %d\n", collisionType);
    //    printBall(ball);
    //mark paddle as disabled
    paddle->disabledCounter = PADDLE_COLLISION_DISABLE_TIME;
    initialBallXVel = ball->xVel;
    initialBallYVel = ball->yVel;
    
    switch(collisionType) {
        case frontCollision:
            //add the paddle's velocity (minus friction) the ball's vel
            setBallXVel(ball->xVel - FPMUL(paddle->xVel, BALL_PADDLE_FRICTION) , ball);
            setBallYVel(ball->yVel + FPMUL(paddle->yVel, BALL_PADDLE_FRICTION), ball);
            
            //mirror paddle x velocity if needed
            if(isPaddleOne) {
                if(paddle->xVel > 0) {
                    bouncePaddleFromBallCollision(paddle, collisionType);
                }
            } else {
                if(paddle->xVel < 0) {
                    bouncePaddleFromBallCollision(paddle, collisionType);
                }
            }
            
            //add parts of the ball velocity to the paddle
            setPaddleXVel(FPMUL(initialBallXVel, PADDLE_FROM_BALL_CONTRIBUTION) + paddle->xVel, paddle);
            setPaddleYVel(FPMUL(initialBallYVel, PADDLE_FROM_BALL_CONTRIBUTION) + paddle->yVel, paddle);
            
            // move ball to "outside" of paddlex
            if(isPaddleOne) {
                ball->x = (paddle->x + paddle->width + epsilon + paddle->xVel);
            } else {
                ball->x = (paddle->x - ball->width - epsilon - paddle->xVel);
            }
            //mirror the xVel
            mirrorBallXVel(ball);
            break;
        case rearCollision:
            //add the paddle's velocity (minus friction) the ball's vel
            setBallXVel(ball->xVel + FPMUL(paddle->xVel, BALL_PADDLE_FRICTION) , ball);
            setBallYVel(ball->yVel + FPMUL(paddle->yVel, BALL_PADDLE_FRICTION), ball);
            // move ball to "outside" of paddlex
            if(isPaddleOne) {
                ball->x = (paddle->x - ball->width - epsilon + paddle->xVel);
            } else {
                ball->x = (paddle->x + paddle->width + epsilon + paddle->xVel);
            }
            break;
        case topCollision:
            //add the paddle's velocity (minus friction) the ball's vel
            setBallYVel(FPMUL(ball->yVel - paddle->yVel, BALL_PADDLE_FRICTION), ball);
            
            //mirror paddle y velocity if needed
            if(paddle->yVel < 0) {
                bouncePaddleFromBallCollision(paddle, collisionType);
            }
            
            //add parts of the ball velocity to the paddle
            setPaddleYVel(FPMUL(initialBallYVel, PADDLE_FROM_BALL_CONTRIBUTION) + paddle->yVel, paddle);
            
            ball->y = (paddle->y - ball->height - epsilon);
            mirrorBallYVel(ball);
            break;
        case bottomCollision:
            //add the paddle's velocity (minus friction) the ball's vel
            setBallYVel(FPMUL(ball->yVel - paddle->yVel, BALL_PADDLE_FRICTION), ball);
            
            //mirror paddle y velocity if needed
            if(paddle->yVel > 0) {
                bouncePaddleFromBallCollision(paddle, collisionType);
            }
            
            //add parts of the ball velocity to the paddle
            setPaddleYVel(FPMUL(initialBallYVel, PADDLE_FROM_BALL_CONTRIBUTION) + paddle->yVel, paddle);
            
            ball->y = (paddle->y + paddle->height + epsilon);
            mirrorBallYVel(ball);
            break;
    }
    
}

void updateBallEastCollision(Ball* ball, Court* court) {
    ball->x = (court->width + court->x - ball->width);
    setBallXVel(FPMUL(ball->xVel, FRICTION), ball);
    setBallYVel(FPMUL(ball->yVel, FRICTION), ball);
    
    mirrorBallXVel(ball);
}

void updateBallWestCollision(Ball* ball, Court *court) {
    ball->x = court->x;
    setBallXVel(FPMUL(ball->xVel, FRICTION), ball);
    setBallYVel(FPMUL(ball->yVel, FRICTION), ball);
    mirrorBallXVel(ball);
}

void updateBallSouthCollision(Ball* ball, Court* court) {
    ball->y = (court->height + court->y - ball->height);
    setBallXVel(FPMUL(ball->xVel, FRICTION), ball);
    setBallYVel(FPMUL(ball->yVel, FRICTION), ball);
    mirrorBallYVel(ball);
}

void updateBallNorthCollision(Ball* ball, Court *court) {
    ball->y = court->y;
    setBallYVel(FPMUL(ball->yVel, FRICTION), ball);
    setBallXVel(FPMUL(ball->xVel, FRICTION), ball);
    mirrorBallYVel(ball);
}

void handleBallCollision(Ball *ball, Court *court, CollisionDirection cd) {
    
    switch (cd) {
    case nCollision:
	updateBallNorthCollision(ball, court);
	break;
    case sCollision:
	updateBallSouthCollision(ball, court);
	break;
    case wCollision:
	updateBallWestCollision(ball, court);
	break;
    case eCollision:
	updateBallEastCollision(ball, court);
	break;
    case nWCollision:
	updateBallNorthCollision(ball, court);
	updateBallWestCollision(ball, court);
	break;
    case nECollision:
	updateBallNorthCollision(ball, court);
	updateBallEastCollision(ball, court);
	break;
    case sWCollision:
	updateBallSouthCollision(ball, court);
	updateBallWestCollision(ball, court);
	break;
    case sECollision:
	updateBallSouthCollision(ball, court);
	updateBallEastCollision(ball, court);
	break;
    case noCollision:
	break;
    default :
	assert(0);
    }   
}

