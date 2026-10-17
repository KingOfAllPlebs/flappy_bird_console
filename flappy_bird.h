// INCLUDE GUARDS /////////////////////////////////////////////////////////////
#ifndef FLAPPY_BIRD_H
#define FLAPPY_BIRD_H

// INCLUDES ///////////////////////////////////////////////////////////////////

#include <stdio.h> // for printf
#include <stdlib.h> // for rand
#include <time.h> // for time
#include <windows.h> // for GetAsyncKeyState & Sleep
#include <stdbool.h> // for true and false
#include <string.h> // for strlen

// GLOBAL CONSTANTS ///////////////////////////////////////////////////////////

// used to initialize the array that holds the ascii
// art displayed as the screen
#define ARRAY_WIDTH 80
#define ARRAY_HEIGHT 24
// constants for the screen size in calculations
// 1 array spot is 4 of these coordinates
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 384
#define SCREEN_TO_ARRAY 0.0625
#define ARRAY_TO_SCREEN 16
// constants for the birds starting position
#define START_X 160
#define START_Y 160
#define START_VELOCITY 0
// constants for the movement
#define JUMP_VELOCITY -28
#define GRAVITY 6
#define MAX_VELOCITY 32
#define MIN_VELOCITY -28
// constants for the pipes
#define PIPE_SPEED -16
#define PIPE_GAP 5
#define PIPE_WIDTH 4
#define MAX_PIPE_Y 298
#define MIN_PIPE_Y 96
// constants for the characters on screen
#define EMPTY_SPACE ' '
#define BIRD_CHAR '@'
#define PIPE_CHAR '#'
#define BORDER_CHAR 'O'
#define TITLE_CHAR '='
// game time control
#define SLEEP_TIME 50

// STRUCTS ///////////////////////////////////////////////////////////////////////

// define the possible game states
typedef enum
{
    START,    // before starting the actual simulations
    PLAYING,  // when the bird is actively flapping
    DEAD      // pause when the player hits a pipe
}
gameState;

// define the bird struct (class's grandpa)
typedef struct bird
{
    float birdX, birdY, birdVelocity;
}
Bird;

// define the pipe struct
typedef struct pipe
{
    float pipeX, pipeY;
}
Pipe;

// FUNCTION PROTOTYPES ////////////////////////////////////////////////////////

// sets all the values in the game to their starting values
void initializeGame(char screen[ARRAY_HEIGHT][ARRAY_WIDTH + 1], Bird* bird,
    Pipe* pipe, gameState* currentState);

// SCREEN FUNCTIONS ///////////////////////////////////////////////////////////

// sets the screen to blank and draws the border
void clearScreen(char screen[ARRAY_HEIGHT][ARRAY_WIDTH + 1]);
// prints out the screen row by row
void printScreen(const char screen[ARRAY_HEIGHT][ARRAY_WIDTH + 1]);
// combines clearScreen drawBird drawPipe and printScreen
void updateScreen(char screen[ARRAY_HEIGHT][ARRAY_WIDTH + 1], Bird bird, 
    Pipe pipe, const char* title, const char* message);
// function to draw a title and a message
void drawTitleMessage(char screen[ARRAY_HEIGHT][ARRAY_WIDTH + 1], 
    const char* title, const char* message);

// BIRD FUNCTIONS /////////////////////////////////////////////////////////////

// draws the bird at it's designated position
void drawBird(char screen[ARRAY_HEIGHT][ARRAY_WIDTH + 1], Bird bird);
// updates the bird's values, specifically position and velocity
void updateBird(Bird* bird);

// PIPE FUNCTIONS /////////////////////////////////////////////////////////////

// draws the pipe at it's designated position
void drawPipe(char screen[ARRAY_HEIGHT][ARRAY_WIDTH + 1], Pipe pipe);
// updates the pipe's values, specifically it's position
void updatePipe(Pipe* pipe);

// COLLISION FUNCTIONS ////////////////////////////////////////////////////////

// check if the bird is at the top or bottom of the screen
bool checkFloorCollision(Bird* bird);

// INPUT FUNCTIONS ////////////////////////////////////////////////////////////

// checks whether space is pressed or not
bool spaceDown();
// checks whether escape is pressed or not
bool quitDown();

// END INCLUDE GUARD //////////////////////////////////////////////////////////
#endif