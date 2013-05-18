#ifndef GPNG_STRUCT_PRINTS
#define GPNG_STRUCT_PRINTS
#include "gameObjects.h"
#include <stdio.h>
void printPaddle(Paddle *paddle);
void printHeaderToStream(FILE * stream, char *name);
void printFooterToStream(FILE *stream);
void printCourt(Court *court);
void printBall(Ball *ball);
void printPaddleToStream(FILE * stream, Paddle* paddle);
void printBallToStream(FILE *stream, Ball* ball);
void printBigFooterToStream(FILE *stream);
#endif
