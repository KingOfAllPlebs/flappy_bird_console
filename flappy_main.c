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
    // initialize the variable to hold the game state
    gameState currentState;
    // initialize all the game's values
    initializeGame(screen, &bird, &pipe, &currentState);
    // runs until you press escape to quit
    while(!quitDown())
    {
        // checks the current game state
        switch(currentState)
        {
            // case when you are in the start screen
            case START:
            {
                // draw the start message on the screen
                updateScreen(screen, bird, pipe, "FLAPPY BIRD", "Press Space To Start");
                // checks if you press space to start
                if(spaceDown())
                {
                    // if so switch the game state to playing
                    currentState = PLAYING;
                }
                break;
            }
            // case when you are actively playing the game
            case PLAYING:
            {
                // updates the values behind the scenes for the bird
                updateBird(&bird);
                // updates the values behind the scenes for the pipe
                updatePipe(&pipe);
                // updates the visuals that you see
                updateScreen(screen, bird, pipe, "", "");
                break;
            }
            // case when the bird dies
            case DEAD:
            {
                // draw the death message on the screen
                //drawDead(screen);
                // checks if you press space to restart
                if(spaceDown())
                {
                    // sets the state back to the playing state
                    currentState = PLAYING;
                }
                break;
            }
        }
        // sleeps until the next frame
        Sleep(SLEEP_TIME);
    }
    // return success
    return 0;
}