#include "title.h"
#include <stdio.h>
#include "cmdString.h"
#include <assert.h>

static char buttonPressed = 0;
static char titleNeedsDisplay = 1;


void titleHandleEvent(void) {
    char joystickEvent;
    volatile char *dataPortA = (char*)0xdc00;

    joystickEvent = *(dataPortA);

    if (!(joystickEvent & 16)) {
	buttonPressed = 1;
    }
}

GPngState titleChangeState(GPngGame *gPngGame) {
    assert(gPngGame != NULL);
    if(buttonPressed) {
	return MENU_STATE;
    } else {
	return TITLE_STATE;
    }
}

void titleDisplay(void) {
    if(titleNeedsDisplay) {
	printLine(2, 2, "hello and welcome to gpng!", 26);
	printLine(2, 3, "gpng is a raquet and ball game", 30);
	printLine(2, 4, "with some simple physics.", 25);
	printLine(2, 5, "the game was made using cc65", 28);
	printLine(2, 6, "(www.cc65.org) - if you are", 27);
	printLine(2, 7, "interested in the source code and", 33);
	printLine(2, 8, "the technical sides of the game", 31);
	printLine(2, 9,  "please visit:", 13);
	printLine(2, 10, "github.com/andrsoze/gpng", 24);
	printLine(2, 14, "i hope you will enjoy gpng :)", 29);
	printLine(2, 15, "//anders persson", 16); 
	printLine(2, 18, "<plug a joystick in to port 2", 29);
	printLine(2, 19, "and press fire to play>", 23);


	titleNeedsDisplay = 0;
    }
}

void titleDisplayInit(void) {
    char *pokePtr;
    pokePtr = ((char*)53280l);
    (*pokePtr) = 0;
    pokePtr++;
    (*pokePtr) = 0;
    pokePtr = ((char*)646);
    (*pokePtr) = 14; //change text to light blue

    titleNeedsDisplay = 1;
    clearScreen();
    titleDisplay();
}

void titleClean(void) {}

void titleRender(void) {}

void titleUpdate(void) {}
