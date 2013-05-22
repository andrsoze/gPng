#include "cmdString.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

void printLine(unsigned char indent, 
	       unsigned char row, 
	       char* lineOfChars,
	       int length)
{
    unsigned char i;
    unsigned char * vidMemDst = (unsigned char*) (VIDEO_SCREEN_START + (COLUMNS_NUM*row) + indent);
    int actualLength = (length + indent > COLUMNS_NUM)?COLUMNS_NUM-indent:length;

    unsigned char uchar_actualLength = (unsigned char)actualLength;
    
    for(i = 0; i < uchar_actualLength; i++){
	
	*(vidMemDst+i)=lineOfChars[i];
    }
}

//25rows*40charcters = 1000
void clearScreen(void)
{
    unsigned char *vidMemPtr;
    unsigned char character = ' ';
    int i;
    
    for(i = 1024; i < 2024; i++) {
	vidMemPtr = (unsigned char *)i;
	(*vidMemPtr)=character;
    }
}

