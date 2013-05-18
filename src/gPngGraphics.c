#include "gPngGraphics.h"
#include "spriteConstants.h"
#include "gPngStructPrint.h"
#include "gPngUtils.h"
#include "cmdString.h"
#include <string.h>
#include "arrowSpriteData.h"

#define PADDLE_SPRITE_LEFT_OFFSET 3

static const unsigned char spriteDataBall[] = {
    56,      0,      0,
    124,      0,      0,
    254,      0,      0,
    254,      0,      0,
    254,      0,      0,
    124,      0,      0,
    56,      0,      0,
    0,      0,      0,
    0,      0,      0,
    0,      0,      0,
    0,      0,      0,
    0,      0,      0,
    0,      0,      0,
    0,      0,      0,
    0,      0,      0,
    0,      0,      0,
    0,      0,      0,
    0,      0,      0,
    0,      0,      0,
    0,      0,      0,
    0,      0,      0
};

static const unsigned char spriteDataPaddle[] =    {
    0x1f, 0x0, 0x0, //0
    0x1f, 0x0, 0x0, //1
    0x1f, 0x0, 0x0, //2
    0x1f, 0x0, 0x0, //3
    0x1f, 0x0, 0x0, //4
    0x1f, 0x0, 0x0, //5
    0x1f, 0x0, 0x0, //6
    0x1f, 0x0, 0x0, //7
    0x1f, 0x0, 0x0, //8
    0x1f, 0x0, 0x0, //9
    0x1f, 0x0, 0x0, //10
    0x1f, 0x0, 0x0, //11
    0x1f, 0x0, 0x0, //12
    0x1f, 0x0, 0x0, //13
    0x1f, 0x0, 0x0, //14
    0x1f, 0x0, 0x0, //15
    0x1f, 0x0, 0x0, //16
    0x1f, 0x0, 0x0, //17
    0x1f, 0x0, 0x0, //18
    0x1f, 0x0, 0x0, //19
    0x1f, 0x0, 0x0, //20
    0x1f, 0x0, 0x0, //21
    0x1f, 0x0, 0x0, //22
    0x1f, 0x0, 0x0, //23
};

void drawBall(Ball * ball)
{
    char * pokePtr;
    char x, y;
	
    //set color, yellow
    pokePtr = (char *)SP0_COLOR;
    (*pokePtr) = 7; 
    
    // set x and y pos
    x = 0xff & FPINT(ball->x);
    y = 0xff & FPINT(ball->y);
    pokePtr = (char *) SP0X;
    *(pokePtr) = x;
    pokePtr = (char *) SP0Y;
    *(pokePtr) = y;
    setMsb(ball->x, 0);
    
    //enable
    pokePtr = (char *) SP_ENABLE;
    *(pokePtr) |= 1;
}

void drawArrow() {
    char *pokePtr;
    char x,y;
 
    x = SCREEN_WIDTH/2;
    x += SCREEN_START_X;
    x -= (SPRITE_WIDTH/2);
    y = SCREEN_HEIGHT/2;
    y += SCREEN_START_Y;
    y -= (SPRITE_HEIGHT/2);

    pokePtr = (char*) SP3X;
    *(pokePtr) = x;
    pokePtr = (char*) SP3Y;
    *(pokePtr) = y;

    //enable
    pokePtr = (char*) SP_ENABLE;
    *(pokePtr) |= 8;  
}

void setupGameColors() {
    char *p = ((char *)53280l); //border
    
    *p = 11;
    *(++p) = 0; //center
}

void drawPaddleSprites(Paddle *paddle1, Paddle *paddle2)
{
    unsigned int x,y;
    char *pokePtr;

    //set color
    pokePtr = (char *)SP1_COLOR;
    if(paddle1->disabledCounter) {
	(*pokePtr) = 10; 
    } else {
	(*pokePtr) = 14; 
    }
    
    //paddle1
    x = FPINT(paddle1->x)-PADDLE_SPRITE_LEFT_OFFSET;
    y = FPINT(paddle1->y);

    pokePtr = (char *) SP1X;
    *(pokePtr) = x;
    pokePtr = (char *) SP1Y;
    *(pokePtr) = y;
    setMsb(paddle1->x, 1);

    //paddle2
	//set color
	pokePtr = (char *)SP2_COLOR;
	if(paddle2->disabledCounter) {
		(*pokePtr) = 10; 
	} else {
		(*pokePtr) = 14; 
	}
	
    x = FPINT(paddle2->x)-PADDLE_SPRITE_LEFT_OFFSET;
    y = FPINT(paddle2->y);

    pokePtr = (char *) SP2X;
    *(pokePtr) = x;
    pokePtr = (char *) SP2Y;
    *(pokePtr) = y;
    setMsb(paddle2->x, 2);

    //enable
    pokePtr = (char *) SP_ENABLE;
    *(pokePtr) |= 6;
}

void setMsb(GPINT x, char index)
{
    char val;
    char * pokePtr = (char *) MSB_HORI_SPRITE;
	
    val = 1 << index;

    if(FPINT(x) > 0xff)
	{
	    *(pokePtr) |= val;
	} else
	{
	    val = (~val);
	    *(pokePtr) &= val;
	}
}


void fillSpriteMem()
{
    char * pokePtr;
    char i;	

    pokePtr = (char *) SP_DATA0;
    for(i = 0; i < 63; i++) {
	*(pokePtr + i) = spriteDataBall[i];
    }

    pokePtr = (char *) SP_DATA1;
    for(i = 0; i < 63; i++) {
	*(pokePtr + i) = spriteDataPaddle[i];
    }

    pokePtr = (char *) SP_DATA2;
    for(i = 0; i < 63; i++) {
	*(pokePtr + i) = spriteDataPaddle[i];
    }
 }

void fillArrowSpriteMem(GravityDirection direction) {
    char *pokePtr;
    char i;

    pokePtr = (char *) SP_DATA3;
    for(i = 0; i < 63; i++) {
	*(pokePtr + i) = spriteDataArrows[direction][i];
    }
}

void setupSpriteMemPtrs()
{
    char * pokePtr;
    
    pokePtr = (char *) SP0_DATAPTR;
    *(pokePtr) = 13;
    pokePtr = (char *) SP1_DATAPTR;
    *(pokePtr) = 14;
    pokePtr = (char *) SP2_DATAPTR;
    *(pokePtr) = 15;
    pokePtr = (char *) SP3_DATAPTR;
    *(pokePtr) = 32;
}

void flashScreen(void)
{
    char i;
    char *p = ((char *)53280l);
    for(i = 0; i < 128; i++) {
	(*p) = i % 15;
    }
    (*p) = 0;
}
static unsigned char playerOneScoreString[13] = "player one: ";
static unsigned char playerTwoScoreString[13] = "player two: ";
static char scorePrintBuffer[20];
void printScores(GPngGame *gPngGame){
    int scoreStrlen;
    
    // print player one
    scoreStrlen = sprintf(scorePrintBuffer, "%s%d", playerOneScoreString, gPngGame->pointsPlayerOne);
    printLine(2, 2, scorePrintBuffer, scoreStrlen);

    // print player two
    scoreStrlen = sprintf(scorePrintBuffer, "%s%d", playerTwoScoreString, gPngGame->pointsPlayerTwo);
    printLine(38-scoreStrlen, 2, scorePrintBuffer, scoreStrlen);

}

void displayWinner(int isPlayerOne)
{
    char * pokePtr;
    clearScreen();
    //disable all sprites
    pokePtr = (char *) SP_ENABLE;
    *(pokePtr) = 0;

    if(isPlayerOne) {
	printLine(10, 12, "player one wins!", 16);
    } else {
	printLine(10, 12, "player two wins!", 16);
    }
    sleepForLoopIterations(1000);
}

