#ifndef GRAVPNG_GRAPHICS
#define GRAVPNG_GRAPHICS

#include "gameObjects.h"
#include "gamePhysicsStructs.h"

void drawBall(Ball * ball);
void drawArrow();
void drawPaddleSprites(Paddle *paddle1, Paddle *paddle2);
void setMsb(GPINT x, char index);
void setupHires(char bgColor, char * colors);
void fillSpriteMem();
void fillArrowSpriteMem(GravityDirection gravityDirection);
void setupSpriteMemPtrs();
void setupMulticolor(char bgColor, char col0, char col1);
void flashScreen(void);
void displayWinner(int isPlayerOne);
void printScores(GPngGame *gPngGame);

#endif

