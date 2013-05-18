gPng
====

*Awesome gravity air shuffle puck for the c64*


gPng is a Shufflepuck - Pong mashup for the c64, with some gravity effects added as an extra spice. It is written in c using the compiler [cc65](http://www.cc65.org).
 
## Building
* Download and install cc65
* Make sure make is installed and working as well
* Clone this repository
* Invoke make with 'make' in the root directory of the repository

This will use the standard cc65 makefile which will build all c files in the src directory. There is a second makefile in the src directory which I have used during development to build tests for specific parts of the game.

## Running the game
To run the game you need an emulator such as [Vice](http://www.viceteam.org). After installing Vice, drag and drop the gPng.c64 which is produced in the build step into the Vice emulator to run the game.
