// header file
#include "flappy_bird.h"

// main program
int main()
{
    char screen[ARRAY_HEIGHT][ARRAY_WIDTH + 1];

    Bird bird;

    initializeGame(screen, &bird);

    while(!quitDown())
    {
        updateScreen(screen, bird);
        updateBird(&bird);
        Sleep(SLEEP_TIME);
    }

    // return success
    return 0;
}