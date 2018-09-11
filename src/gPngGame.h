#ifndef GRAVPNGGAME_H_
#define GRAVPNGGAME_H_
#include "gameObjects.h"
#include "gameState.h"

#define C64_EPSILON FPMAKE(2,8)
#define FINAL_GAME_SCORE 3

//playerOneGoal, playerTwoGoal, noGoal
typedef enum GRAVPNG_GAME_SCORE_CHANGE {
    PLAYER_ONE_GOAL,
    PLAYER_TWO_GOAL,
    NO_GOAL
} GravPngScoreChange;

void gameUpdate(GPngGame *gPngGame);
void resetPongGame(GPngGame *gPngGame);
void gameRenderGame(GPngGame *gPngGame);
GPngState gameChangeState(GPngGame * gPngGame);
void gameDisplayInit(void);
void gameClean(void);
//private
GravPngScoreChange updatePongGame(GPngGame *gPngGame);
void updatePongGamePositions(Ball *ball, Paddle *paddleOne, Paddle *paddleTwo);
void handlePlayerInput(GPngGame *gPngGame, int isPlayerOne);
#endif /* GRAVPNGGAME_H_ */
