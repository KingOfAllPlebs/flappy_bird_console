// header file
#include "flappy_bird.h"

// main program
int main()
{
    // initialize the 2d array that holds the screen
    char screen[ARRAY_HEIGHT][ARRAY_WIDTH + 1];
    // initialize the bird that you will control in the game
    Bird bird;
    // initialize the pipe that the bird will avoid
    Pipe pipe;
    // initialize all the game's values
    initializeGame(screen, &bird, &pipe);
    // runs until you press escape to quit
    while(!quitDown())
    {
        // updates the visuals that you see
        updateScreen(screen, bird, pipe);
        // updates the values behind the scenes for the bird
        updateBird(&bird);

        updatePipe(&pipe);
        // sleeps until the next frame
        Sleep(SLEEP_TIME);
    }
    // return success
    return 0;
}