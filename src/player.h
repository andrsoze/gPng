#ifndef PLAYER_H
#define PLAYER_H

#include "gPngMath.h"
#include "gameObjects.h"

#define PLAYER_INPUT_STEP FPMAKE(0,5)
void playerOneInput(GPngGame *gPngGame);
void playerTwoInput(GPngGame *gPngGame);
void realPlayerOneInput(GPngGame *gPngGame);
void realPlayerTwoInput(GPngGame *gPngGame);
#endif
