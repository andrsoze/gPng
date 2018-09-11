#ifndef GRAVPNG_H
#define GRAVPNG_H
#include "gameState.h"

static GameState *globalGameState;



void runLoop(void);
void changeState(GPngState newState);
void setupInterrupt();






#endif
