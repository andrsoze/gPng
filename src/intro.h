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
void introClean();
GPngState introChangeState();
//--graphics
void setupIntroSpriteMemPtrs();
void fillIntroSpriteMem();
void drawSprite();
//--menu
void moveMenuUp();
void moveMenuDown();

#endif
