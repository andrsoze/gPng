#ifdef TARGET_TEST
#include "spriteConstants.h"
#include "gPngGraphics.h"
#include "arrowSpriteData.h"
#include <stdio.h>

void testSprites();
void displaySprites();

int main(void) {
    testSprites();
    while(1) {}
    return 1;
}

void testSprites() {
    unsigned int loopCounter;
    int i, j, tmp;
    unsigned char *pokePtr;

    //set up the dataPointers
    j=32;
    for(i=0;i < 8; i++) {
	pokePtr = (char*)(SP0_DATAPTR+i);
	(*pokePtr) = j++;
    }

    //load the sprites
    j=0;

    for(i = 0; i < 64; i++) {
	loopCounter =   (SP_DATA3 + i);
	pokePtr = (unsigned char *)  (loopCounter);

	(*pokePtr) = spriteDataArrows[0][i];
	
    }
    
    for(i = 0; i < 64; i++) {
	pokePtr = (unsigned char *)  (SP_DATA4 + i);
	
	(*pokePtr) = spriteDataArrows[1][i];
	
    }
    
    for(i = 0; i < 64; i++) {
	pokePtr = (unsigned char *)  (SP_DATA5 + i);
	
	(*pokePtr) = spriteDataArrows[2][i];
    }
    
    for(i = 0; i < 64; i++) {
	pokePtr = (unsigned char *)  (SP_DATA6 + i);
	
	(*pokePtr) = spriteDataArrows[3][i];
	
    }
    
    for(i = 0; i < 64; i++) {
	pokePtr = (char *)  (SP_DATA7 + i);
	
	(*pokePtr) = spriteDataArrows[4][i];
    }


    for(i = 0; i < 64; i++) {
	pokePtr = (char *)  (SP_DATA7 + 0x40 + i);
	
	(*pokePtr) = spriteDataArrows[5][i];
	
    }
    pokePtr =(unsigned char *) SP_DATA6;
    for(i = 0; i < 64; i++) {
	pokePtr = (char *)  (SP_DATA7 + 0x80 + i);
	
	(*pokePtr) = spriteDataArrows[6][i];
	
    }
    for(i = 0; i < 64; i++) {
	pokePtr = (char *)  (SP_DATA7 + 0xC0 + i);
	
	(*pokePtr) = spriteDataArrows[7][i];
	
    }

    //set up colors
    for(i=0;i<8;i++) {
	pokePtr = (char*)(SP0_COLOR+i);
	(*pokePtr)=0;
    }

    //setup x and y coords
    for(i=0;i<8;i++) {
	pokePtr=(char*)(SP0X+(i*2));
	(*pokePtr)=(25+25*(1+i));
	pokePtr=(char*)(SP0Y+(i*2));
	(*pokePtr)=(50);
    }

    //enable all
    pokePtr = (char *) SP_ENABLE;
    *(pokePtr) = 255;
}

void displaySprites() {
    

}


#endif
