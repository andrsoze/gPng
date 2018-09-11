#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "gameObjects.h"

void test();

typedef enum PNG_STATE {
    MENU_STATE = 0,
    HIGHSCORE_STATE = 1,
    GAME_STATE_SINGLE = 2,
    GAME_STATE_DOUBLE = 3,
    TITLE_STATE = 4,
    HOW_TO_PLAY_STATE = 5
    
  } GPngState;


typedef struct GAME_STATE {
    int gamesStateId;
    void (*initFPtr)(void);
    void (*handleEventFPtr)(void);
    void (*updateFPtr)(void);
    void (*renderFPtr)(void);
    void (*clean)(void);
    GPngState (*changeState)(GPngGame*);
} GameState;


#endif
