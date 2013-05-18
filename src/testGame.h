#ifndef TEST_GAME_H
#define TEST_GAME_H


#include "gameObjects.h"
#include "gamePhysics.h"
#include <assert.h>
#include <stdio.h>
#include "gPngStructPrint.h"

void collidePaddleOneWithCourt_shouldZeroVelAndResetPositions(void);
void collidePaddleTwoWithCourt_shouldZeroVelAndResetPositions(void);
void collidePaddleOneWithCourt_shouldReturnCorrectCD(void);
void collidePaddleTwoWithCourt_shouldReturnCorrectCD(void);
void collidePaddleOneWithCourt_shouldNotDoAnythingIfNoColl(void);
void collidePaddleTwoWithCourt_shouldNotDoAnythingIfNoColl(void);







#endif
