#include "intro.h"
#include "gameState.h"
#include <stdio.h>
#include "cmdString.h"
#include "spriteConstants.h"
#include "gameObjects.h"
#include "gPngGraphics.h"
#include "gPngUtils.h"
#include <assert.h>

#define INDENT 4
#define ROW_SPACING 5
#define INITIAL_ROW_SPACE 6

static char buttonPressed;
void initGameObjects(int isOnePlayer, GPngGame *gPngGame);

//graphics
void fillSpriteMem();

char menuAlternativeStrings[][20] = { "one player game", "two player game",
				      "how to play" };

char menuAlternativeStringLengths[3] = { 15, 15, 11 };

enum MenuAlternative selectedAlternative = TwoPlayerGame;

unsigned char needsRedraw = 1;

void introRender(void) {
    drawSprite();
}

char count = 0;
void introHandleEvent(void) {
    char joystickEvent;
    volatile char *dataPortA = (char*) 0xdc00;
    joystickEvent = *(dataPortA);
    
    if (++count < 56) {
	return;
    }
    
    count = 0;

    if (!(joystickEvent & 1)) {
	//pressedUp
	moveMenuUp();
    } else if (!(joystickEvent & 2)) {
	//pressed down
	moveMenuDown();
    } else if (!(joystickEvent & 16)) {
	//pressed fire
	buttonPressed = 1;
    }

}

void moveMenuUp() {
    if (selectedAlternative == TwoPlayerGame) {
	selectedAlternative = OnePlayerGame;
    } else if (selectedAlternative == HowToPlay) {
	selectedAlternative = TwoPlayerGame;
    }
}

void moveMenuDown() {
    if (selectedAlternative == OnePlayerGame) {
	selectedAlternative = TwoPlayerGame;
    } else if (selectedAlternative == TwoPlayerGame) {
	selectedAlternative = HowToPlay;
    }
}

void introUpdate() {

}

GPngState introChangeState(GPngGame *gPngGame) {
    if (buttonPressed) {
	buttonPressed = 0;
	if (selectedAlternative == OnePlayerGame) {
	    initGameObjects(1, gPngGame);
	    return GAME_STATE_SINGLE;
	} else if (selectedAlternative == TwoPlayerGame) {
	    initGameObjects(0, gPngGame);
	    return GAME_STATE_DOUBLE;
	} else if (selectedAlternative == HowToPlay) {
	    return HOW_TO_PLAY_STATE;
	} else {
	    return MENU_STATE;
	}
    } else {
	return MENU_STATE;
    }
}

void setIntroNeedsRedraw(unsigned char nextNeedsRedraw) {
    needsRedraw = nextNeedsRedraw;
}

void introDisplayInit(void) {

    if (needsRedraw) {
	int i;

	fillIntroSpriteMem();
	setupIntroSpriteMemPtrs();
	drawSprite();		
	clearScreen();
	for (i = 0; i < 3; i++) {
	    printLine(INDENT, INITIAL_ROW_SPACE + (i * ROW_SPACING),
		      menuAlternativeStrings[i], menuAlternativeStringLengths[i]);
	}
    }
}

void introClean() {
    
}

//--graphics
void setupIntroSpriteMemPtrs() {
    char * pokePtr;
    
    pokePtr = (char *) SP0_DATAPTR;
    *(pokePtr) = 13;
}

void fillIntroSpriteMem() {
    char * pokePtr;
    char i;
    
    for (i = 0; i < 63; i++) {
	pokePtr = (char *) SP_DATA0;
	*(pokePtr + i) = 255;
    }
}

void drawSprite() {
    unsigned int x, y;
    char *pokePtr;
    // calc x
    // first alt = INITIAL_ROW_SPACE*8+(21/2)
    // set x and y pos
    x = 26;
    y = ((INITIAL_ROW_SPACE + 1) * 8) + 36;

    if (selectedAlternative == TwoPlayerGame) {
	y += (ROW_SPACING * 8);
    } else if (selectedAlternative == HowToPlay) {
	y += ((ROW_SPACING * 2) * 8);
    }

    //set color, yellow
    pokePtr = (char *)SP0_COLOR;
    (*pokePtr) = 1; //white 

    pokePtr = (char *) SP0X;
    *(pokePtr) = x;
    setMsb(0, 0);
    pokePtr = (char *) SP0Y;
    *(pokePtr) = y;

    //enable
    pokePtr = (char *) SP_ENABLE;
    *(pokePtr) = 1; //disable all other sprites
}

void initGameObjects(int isOnePlayer, GPngGame *gPngGame)
{
    initDefaultBall(gPngGame->ball);
    initDefaultCourt(gPngGame->court);
    initDefaultPaddleOne(gPngGame->paddleOne);
    initDefaultPaddleTwo(gPngGame->paddleTwo);

    gPngGame->isPlayerOneHuman = 1;
    if(isOnePlayer) {
	gPngGame->isPlayerTwoHuman = 0;
    } else {
	gPngGame->isPlayerTwoHuman = 1;
    }
}
