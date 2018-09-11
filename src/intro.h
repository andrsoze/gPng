#ifndef INTRO_H
#define INTRO_H
#include "gameState.h"
#include "spriteConstants.h"

// Menu alternatives: one player, two player, high score list
enum MenuAlternative {
  OnePlayerGame = 1,
  TwoPlayerGame = 2,
  HowToPlay = 3
};



void setIntroNeedsRedraw(unsigned char nextNeedsRedraw);
void introDisplayInit(void);
void introHandleEvent(void);
void introUpdate(void);
void introRender(void);
void introClean(void);
GPngState introChangeState(GPngGame *gPngGame);
//--graphics
void setupIntroSpriteMemPtrs(void);
void fillIntroSpriteMem(void);
void drawSprite(void);
//--menu
void moveMenuUp(void);
void moveMenuDown(void);

#endif
