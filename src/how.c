#include "how.h"
#include <stdio.h>
#include <assert.h>
#include "cmdString.h"
#include "spriteConstants.h"

static char buttonPressed = 0;
static char howNeedsDisplay = 1;


void howHandleEvent(void) {
    char joystickEvent;
    volatile char *dataPortA = (char*)0xdc00;

    joystickEvent = *(dataPortA);

    if (!(joystickEvent & 16)) {
	buttonPressed = 1;
    } 
}

GPngState howChangeState(GPngGame *gPngGame) {
    assert(gPngGame != NULL);
    if(buttonPressed) {
	return MENU_STATE;
    } else {
	return HOW_TO_PLAY_STATE;
    }
}

void howDisplay(void) {

    if(howNeedsDisplay) {
	printLine(2, 2, "how to play", 11);
	printLine(2, 4, "accelerate your racquet by pressing", 35);
	printLine(2, 5, "up, down, left or right. try to hit", 35);
	printLine(2, 6, "the ball with speed; the speed will", 35);
	printLine(2, 7, "partly be transfered to the ball.", 33);
	printLine(2, 9, "the arrow in the center of the", 30);
	printLine(2,10, "screen indicates the direction of", 33);
	printLine(2,11, "gravity. the direction will change", 34);
	printLine(2,12, "every third time the ball hits a", 32);
	printLine(2,13, "racquet. no arrow = no gravity.", 31);

	printLine(2,15, "the player who first reaches a score", 36);
	printLine(2,16, "of 3 wins the game.", 19);
	howNeedsDisplay = 0;
    }
}

void howDisplayInit(void) {
    char *pokePtr;
    pokePtr = ((char*)53280l);
    (*pokePtr) = 0;
    pokePtr++;
    (*pokePtr) = 0;

    howNeedsDisplay = 1;
    buttonPressed = 0;

    clearScreen();
    //disable all sprites
    pokePtr = (char *) SP_ENABLE;
    *(pokePtr) = 0;
    howDisplay();
}

void howClean(void) {}

void howRender(void) {}

void howUpdate(void) {}
