#ifndef CMD_STRING_H
#define CMD_STRING_H

#define VIDEO_SCREEN_START (1024)
#define ROWS_NUM (30)
#define COLUMNS_NUM (40)

void printLine(unsigned char indent, 
	       unsigned char row, 
	       char* lineOfChars,
	       int length); 

void clearScreen(void);

#endif
