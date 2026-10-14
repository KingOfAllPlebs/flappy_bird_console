// header file
#include "flappy_bird.h"

void initializeGame(char screen[ARRAY_HEIGHT][ARRAY_WIDTH + 1], Bird* bird)
{
    clearScreen(screen);
    bird->birdX = START_X;
    bird->birdY = START_Y;
    bird->birdVelocity = START_VELOCITY;
}

// 0. takes the screen pointer as a parameter
// 1. clears the console
// 2. Loops through the array and sets the border to O
//    and everything else blank
void clearScreen(char screen[ARRAY_HEIGHT][ARRAY_WIDTH + 1])
{
    // this string clears the console for some reason??
    printf("\e[1;1H\e[2J");
    // does 2 for loops to loop throug the whole screen 2d array
    for(int i = 0; i < ARRAY_HEIGHT; i++)
    {
        for(int j = 0; j < ARRAY_WIDTH; j++)
        {
            // checks if its the top or bottom row
            if(i == 0 || i == ARRAY_HEIGHT - 1)
            {
                // sets those spots to the border character
                screen[i][j] = BORDER_CHAR;
            }
            // checks if its the first or last column
            else if(j == 0 || j == ARRAY_WIDTH - 1)
            {
                // sets those spots to the border character
                screen[i][j] = BORDER_CHAR;
            }
            // if its not part of the border
            else
            {
                // sets those spots to empty space
                screen[i][j] = EMPTY_SPACE;
            }
        }
        // adds the null character to the end of each row
        // so each row can be printed as a string
        screen[i][ARRAY_WIDTH] = '\0';
    }
}

// 0. takes the screen pointer as a parameter but keep it constant
// 1. loop through the whole 2d array
// 2. print out each row as a string on a new line
void printScreen(const char screen[ARRAY_HEIGHT][ARRAY_WIDTH + 1])
{
    // loops through each row of the array
    for(int i = 0; i < ARRAY_HEIGHT; i++)
    {
        // prints out each row as a string
        printf("%s\n", screen[i]);
    }
}

// 0. takes the screen pointer as a parameter
// 0. takes the bird's position as a parameter
// 1. convert the bird's position to an array position
// 2. loop through the spots all around the bird position
//    to create a 3x3 grid of @s to be the bird
void drawBird(char screen[ARRAY_HEIGHT][ARRAY_WIDTH + 1], Bird bird)
{
    // converts the birds position to the array position
    int birdXArray = bird.birdX * SCREEN_TO_ARRAY;
    int birdYArray = bird.birdY * SCREEN_TO_ARRAY;
    // loops thorugh the spots all around the bird's main position
    for(int i = birdXArray - 1; i <= birdXArray + 1; i++)
    {
        for(int j = birdYArray - 1; j <= birdYArray + 1; j++)
        {
            // sets the 3x3 of @s to represent the bird
            screen[j][i] = BIRD_CHAR;
        }
    }
    screen[birdYArray][birdXArray + 2] = BIRD_CHAR;
}

// 0. takes the screen pointer as a parameter
// 0. takes the bird's position as a parameter
// 1. clears the screen
// 2. draws the bird
// 3. prints the updated screen
void updateScreen(char screen[ARRAY_HEIGHT][ARRAY_WIDTH + 1], Bird bird)
{
    clearScreen(screen);
    drawBird(screen, bird);
    printScreen(screen);
}

bool spaceDown()
{
    return (GetAsyncKeyState(VK_SPACE) & 0x8000) != 0;
}

bool quitDown()
{
    return (GetAsyncKeyState(VK_ESCAPE) & 0x8000) != 0;
}

void updateBird(Bird* bird)
{
    if(spaceDown())
    {
        bird->birdVelocity = JUMP_VELOCITY;
    }
    else
    {
        if(bird->birdVelocity < MAX_VELOCITY)
        {
            bird->birdVelocity += GRAVITY;
        }
        else
        {
            bird->birdVelocity = MAX_VELOCITY;
        }
    }

    bird->birdY += bird->birdVelocity;

    if(bird->birdY < 0 + ARRAY_TO_SCREEN)
    {
        bird->birdY = 0 + ARRAY_TO_SCREEN;
    }
    else if(bird->birdY > SCREEN_HEIGHT - ARRAY_TO_SCREEN * 2)
    {
        bird->birdY = SCREEN_HEIGHT - ARRAY_TO_SCREEN * 2;
    }
}