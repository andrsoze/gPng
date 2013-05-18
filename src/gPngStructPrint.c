#include "gPngStructPrint.h"
int debugPrintCount = 0;

void printPaddleToStream(FILE * stream, Paddle* paddle)
{
#ifndef NO_DEBUG_PRINT
    char paddleStr[7] = "PADDLE";
    printHeaderToStream(stream, paddleStr);
    fprintf(stream, "x: %d.%d\n", FPINT(paddle->x), FPFRAC(paddle->x));
    fprintf(stream, "y: %d.%d\n", FPINT(paddle->y), FPFRAC(paddle->y));
    fprintf(stream, "xVel: %d.%d\n", FPINT(paddle->xVel), FPFRAC(paddle->xVel));
    fprintf(stream, "yVel: %d.%d\n", FPINT(paddle->yVel), FPFRAC(paddle->yVel));
    fprintf(stream, "height: %d.%d\n", FPINT(paddle->height), FPFRAC(paddle->height));
    fprintf(stream, "width: %d.%d\n", FPINT(paddle->width), FPFRAC(paddle->width));
    printFooterToStream(stream);
#endif
}

void printPaddle(Paddle *paddle)
{
#ifndef NO_DEBUG_PRINT
    printPaddleToStream(stdout, paddle);
#endif
}

void printBallToStream(FILE *stream, Ball* ball)
{
#ifndef NO_DEBUG_PRINT
    char ballStr[5] = "BALL";
    printHeaderToStream(stream, ballStr);
    fprintf(stream, "x: %d.%d -- %d\n", FPINT(ball->x), FPFRAC(ball->x), ball->x);
    fprintf(stream, "y: %d.%d -- %d\n", FPINT(ball->y), FPFRAC(ball->y), ball->y);
    fprintf(stream, "xVel: %d.%d\n", FPINT(ball->xVel), FPFRAC(ball->xVel));
    fprintf(stream, "yVel: %d.%d\n", FPINT(ball->yVel), FPFRAC(ball->yVel));
    fprintf(stream, "height: %d.%d\n", FPINT(ball->height), FPFRAC(ball->height));
    fprintf(stream, "width: %d.%d\n", FPINT(ball->width), FPFRAC(ball->width));
    printFooterToStream(stream);
#endif
}

void printBall(Ball *ball)
{
#ifndef NO_DEBUG_PRINT
    printBallToStream(stdout, ball);
#endif
}

void printCourtToStream(FILE *stream, Court* court) {
#ifndef NO_DEBUG_PRINT
    char courtStr[6] = "COURT";
    printHeaderToStream(stream, courtStr);
    fprintf(stream, "width: %d.%d\n", FPINT(court->width), FPFRAC(court->width));
    fprintf(stream, "height: %d.%d\n", FPINT(court->height), FPFRAC(court->height));
    fprintf(stream, "x: %d.%d\n", FPINT(court->x), FPFRAC(court->y));
    fprintf(stream, "y: %d.%d\n", FPINT(court->y), FPFRAC(court->y));
    fprintf(stream, "leftAccAreaX: %d.%d\n", FPINT(court->leftAccAreaX),
	    FPFRAC(court->leftAccAreaX));
    fprintf(stream, "leftAccAreaWidth: %d.%d\n", FPINT(court->leftAccAreaWidth),
	    FPFRAC(court->leftAccAreaWidth));
    fprintf(stream, "rightAccAreaX: %d.%d\n", FPINT(court->rightAccAreaX),
	    FPFRAC(court->rightAccAreaX));
    fprintf(stream, "rightAccAreaWidth: %d.%d\n", FPINT(court->rightAccAreaWidth),
	    FPFRAC(court->rightAccAreaWidth));
    printFooterToStream(stream);
#endif
}

void printCourt(Court *court)
{
#ifndef NO_DEBUG_PRINT
    printCourtToStream(stdout, court);
#endif
}

void printHeaderToStream(FILE *stream, char *name)
{ 
#ifndef NO_DEBUG_PRINT
    fprintf(stream, "**********************\n");
    fprintf(stream, "*******%s********\n", name);
#endif
}

void printFooterToStream(FILE *stream)
{
#ifndef NO_DEBUG_PRINT
    fprintf(stream, "**********************\n\n");
#endif
}

void printBigFooterToStream(FILE *stream)
{
#ifndef NO_DEBUG_PRINT
    fprintf(stream, "********************************************************************\n");
    fprintf(stream, "----------------------------%d--------------------------------------\n", ++debugPrintCount);
    fprintf(stream, "********************************************************************\n");
#endif

}
