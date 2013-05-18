SOURCES = cmdString.c intro.c gPng.c gamePhysics.c
CC65_HOME=/usr/local
PROGRAM = gpng testPhysics testPong

ifdef CC65_TARGET
CC      = $(CC65_HOME)/bin/cl65 -DTARGET_C64 -DTARGET_TEST -O3
else
CC      = gcc
CFLAGS  = -MMD -MP -O3
LDFLAGS = -Wl,-Map,$(PROGRAM).map
endif

########################################

.SUFFIXES:
.PHONY: all
all: $(PROGRAM)

ifneq ($(MAKECMDGOALS),clean)
-include $(SOURCES:.c=.d)
endif

game: gPngStructPrint.c gameObjects.c gamePhysics.c gamePhysicsBall.c gPngGraphics.c gPngGame.c player.c cmdString.c intro.c gPng.c gPngUtils.c title.c how.c
	$(CC) gPngStructPrint.c gameObjects.c gamePhysics.c gamePhysicsBall.c gPngGraphics.c gPngGame.c player.c cmdString.c intro.c gPng.c gPngUtils.c title.c how.c -o gPng $(CFLAGS)

testGame:
	$(CC) gPngStructPrint.c gameObjects.c gamePhysics.c game.c testGame.c -o testPong 

testGamePhysics:
	$(CC) gPngStructPrint.c gameObjects.c gamePhysics.c gamePhysicsBall.c testBallPhysics.c -o testPongPhysics $(CFLAGS)

testGameLoop: gPngStructPrint.c gameObjects.c gamePhysics.c gamePhysicsBall.c testGameLoop.c gPngGraphics.c gPngGame.c player.c cmdString.c gPngUtils.c
	$(CC) gPngStructPrint.c gameObjects.c gamePhysics.c gamePhysicsBall.c testGameLoop.c gPngGraphics.c gPngGame.c player.c cmdString.c gPngUtils.c -o testGameLoop $(CFLAGS)

testGameLoopGraphics: gPngStructPrint.c gameObjects.c gamePhysics.c gamePhysicsBall.c gPngGraphics.c testGameLoopGraphics.c
	$(CC) gPngStructPrint.c gameObjects.c gamePhysics.c gamePhysicsBall.c gPngGraphics.c testGameLoopGraphics.c -o testGameLoopGraphics $(CFLAGS)

testGameMath: testMath.c
	$(CC) testMath.c -o testGameMath $(CFLAGS)

testCollision: gPngStructPrint.c gameObjects.c gamePhysics.c gamePhysicsBall.c gPngGraphics.c gPngGame.c player.c cmdString.c gPngUtils.c testCollision.c
	$(CC) gPngStructPrint.c gameObjects.c gamePhysics.c gamePhysicsBall.c  gPngGraphics.c gPngGame.c player.c cmdString.c gPngUtils.c testCollision.c -o testCollision $(CFLAGS)

clean:
	rm -f $(SOURCES:.c=.o) $(SOURCES:.c=.d) $(SOURCES:.c=.c~) $(SOURCES:.c=.h~) $(PROGRAM) $(PROGRAM).map

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
	@$(MAKEDEPEND)

$(PROGRAM): $(SOURCES:.c=.o)
	$(CC) $(LDFLAGS) $^ -o $@
