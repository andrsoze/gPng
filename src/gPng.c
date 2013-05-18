#include "gPng.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "intro.h"
#include "gameObjects.h"
#include "gPngGame.h"
#include "gPngUtils.h"
#include "gPngGraphics.h"
#include "player.h"
#include "title.h"
#include "how.h"

static GPngState currentGPngState = TITLE_STATE;

Ball ball;
Paddle paddleOne;
Paddle paddleTwo;
Court court;
GPngGame gPngGame;

void assembleDefaultPongGame();
void setupNewGame(int numHumanPlayers);
void runLoopGame();

int main()
{
    globalGameState = malloc(sizeof(GameState));

    globalGameState->initFPtr = titleDisplayInit;
    globalGameState->handleEventFPtr = titleHandleEvent;
    globalGameState->updateFPtr = titleUpdate;
    globalGameState->renderFPtr = titleRender;
    globalGameState->clean = titleClean;
    globalGameState->changeState = titleChangeState;

    //init pong game
    assembleDefaultPongGame();

    //init first graphics
    globalGameState->initFPtr();
    
    runLoop();

    while(1){
	//do nada
    }
    
    free(globalGameState);
    return 1;
    
}

void runLoop()
{
    GPngState newState;


    while(1) {
	if(currentGPngState == GAME_STATE_SINGLE || 
		  currentGPngState == GAME_STATE_DOUBLE) {
	    runLoopGame();
	} else {
	        globalGameState->handleEventFPtr();
		 globalGameState->updateFPtr();
		 globalGameState->renderFPtr();
		 newState = globalGameState->changeState(&gPngGame);
		 
		 if(currentGPngState != newState) {
		     changeState(newState);
		 }
	}
    }
 }

void runLoopGame() {
    GravPngScoreChange scoreChange;

    scoreChange = updatePongGame(&gPngGame);
    if(scoreChange == PLAYER_ONE_GOAL || scoreChange == PLAYER_TWO_GOAL) {
	flashScreen();
	currentGPngState = gameChangeState(&gPngGame);
	if(currentGPngState == MENU_STATE) {
	    setIntroNeedsRedraw(1);
	    introDisplayInit();
	    return;
	} else {		


	    resetPongGame(&gPngGame);

	    printScores(&gPngGame);
	}
    }
    handlePlayerInput(&gPngGame, 1);
    handlePlayerInput(&gPngGame, 0);
    gameRenderGame(&gPngGame);
}

void changeState(GPngState newState) {
    currentGPngState = newState;
    //change state

    switch (newState) {
    case GAME_STATE_SINGLE:
	setupNewGame(1);
	break;
    case GAME_STATE_DOUBLE:
	setupNewGame(2);
	break;
    case HOW_TO_PLAY_STATE:
	globalGameState->initFPtr = howDisplayInit;
	globalGameState->handleEventFPtr = howHandleEvent;
	globalGameState->updateFPtr = howUpdate;
	globalGameState->renderFPtr = howRender;
	globalGameState->clean = howClean;
	globalGameState->changeState = howChangeState;
	globalGameState->initFPtr();
	break;
    case MENU_STATE:
	globalGameState->initFPtr = introDisplayInit;
	globalGameState->handleEventFPtr = introHandleEvent;
	globalGameState->updateFPtr = introUpdate;
	globalGameState->renderFPtr = introRender;
	globalGameState->clean = introClean;
	globalGameState->changeState = introChangeState;
	globalGameState->initFPtr();
	break;
    default:
	assert(0); //only states supported are single and doulbe game
    }
}

void setupNewGame(int numHumanPlayers) {
    assert(numHumanPlayers >= 0 && numHumanPlayers < 3);
    gameDisplayInit();
    resetPongGame(&gPngGame);

    gPngGame.pointsPlayerOne = 0;
    gPngGame.pointsPlayerTwo = 0;
    gPngGame.isPlayerOneHuman = 1;
    gPngGame.isPlayerTwoHuman = (numHumanPlayers == 2)?1:0;

    printScores(&gPngGame);
}

void assembleDefaultPongGame() {
    gPngGame.ball = &ball;
    gPngGame.paddleOne = &paddleOne;
    gPngGame.paddleTwo = &paddleTwo;
    gPngGame.court = &court;
    gPngGame.useGravity = 1;
    gPngGame.gravity = 1;
    gPngGame.epsilon = FPMAKE(2,8);

    gPngGame.pointsPlayerOne = 0;
    gPngGame.pointsPlayerTwo = 0;
}


