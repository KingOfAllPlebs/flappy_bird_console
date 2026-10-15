// header file
#include "flappy_bird.h"

// 0. takes the screen pointer as a parameter
// 0. takes the bird as a parameter
// 0. takes the pipe as a parameter
// 1. makes sure the screen is blank to start
// 2. sets the initial values for the bird
// 3. sets the initial values for the pipe
void initializeGame(char screen[ARRAY_HEIGHT][ARRAY_WIDTH + 1], Bird* bird, Pipe* pipe, gameState* currentState)
{
    // make sure the screen is blank
    clearScreen(screen);
    // sets the bird's values to their starting values
    bird->birdX = START_X;
    bird->birdY = START_Y;
    bird->birdVelocity = START_VELOCITY;
    // sets the pipe's values to their starting values
    pipe->pipeX = SCREEN_WIDTH;
    pipe->pipeY = SCREEN_HEIGHT / 2;
    // set the gameState to the starting state
    *currentState = START;
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
// 0. takes the bird as a parameter
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
// 0. takes the bird as a parameter
// 1. clears the screen
// 2. draws the bird
// 3. prints the updated screen
void updateScreen(char screen[ARRAY_HEIGHT][ARRAY_WIDTH + 1], Bird bird, Pipe pipe)
{
    clearScreen(screen);
    drawPipe(screen, pipe);
    drawBird(screen, bird);
    printScreen(screen);
}

// 0. returns true when space is held and false when it is not
bool spaceDown()
{
    // uses the windows.h library to get if the space key is pressed
    return (GetAsyncKeyState(VK_SPACE) & 0x8000) != 0;
}

// 0. returns true when escape is held and false when it is not
bool quitDown()
{
    // uses the windows.h library to get if the escape key is pressed
    return (GetAsyncKeyState(VK_ESCAPE) & 0x8000) != 0;
}

// 0. takes the bird as a parameter
// 1. checks if space is held and if so it makes the bird's
//    velocity the JUMP_VELOCITY
// 2. if space is not held then it adds GRAVITY to the velocity
//    unless the velocity would be over MAX_VELOCITY
// 3. adds the velocity of the bird to its y position
// 4. makes sure the bird is within the bounds of the screen
void updateBird(Bird* bird)
{
    // checks if space is being held
    if(spaceDown())
    {
        // if it is then make the velocity equal to JUMP_VELOCITY
        bird->birdVelocity = JUMP_VELOCITY;
    }
    // if space is not being held
    else
    {
        // checks if the velocity is under MAX_VELOCITY
        if(bird->birdVelocity < MAX_VELOCITY)
        {
            // if so then it can add GRAVITY to the velocity
            bird->birdVelocity += GRAVITY;
        }
        // if the velocity is over MAX_VELOCITY
        else
        {
            // sets the velocity to MAX_VELOCITY so it doesn't
            // get too fast
            bird->birdVelocity = MAX_VELOCITY;
        }
    }
    // adds the bird's velocity to the bird's y position
    bird->birdY += bird->birdVelocity;
    // checks if the bird would be above the screen
    if(bird->birdY < 0 + ARRAY_TO_SCREEN)
    {
        // in that case keep it at the top of the screen
        bird->birdY = 0 + ARRAY_TO_SCREEN;
    }
    // checks if the bird would be below the screen
    else if(bird->birdY > SCREEN_HEIGHT - ARRAY_TO_SCREEN * 2)
    {
        // in that case keep it at the bottom of the screen
        bird->birdY = SCREEN_HEIGHT - ARRAY_TO_SCREEN * 2;
    }
}

// 0. takes the screen pointer as a parameter
// 0. takes the pipe as a parameter
// 1. converts the pipes coordinates to array coordinates
// 2. draws the pipe within the bounds of the screen
//    and with a designated width and gap size
void drawPipe(char screen[ARRAY_HEIGHT][ARRAY_WIDTH + 1], Pipe pipe)
{
    // converts the pipes coordinates to the array coordinates
    int pipeXArray = pipe.pipeX * SCREEN_TO_ARRAY;
    int pipeYArray = pipe.pipeY * SCREEN_TO_ARRAY;
    // loops from the top of the screen to the bottom
    for(int i = 1; i < ARRAY_HEIGHT - 1; i++)
    {
        // loops from the left side of the pipe to the right
        for(int j = pipeXArray - PIPE_WIDTH; j < pipeXArray + PIPE_WIDTH; j++)
        {
            // makes sure the pipe is within the screen horizontally
            if((j > 0 && j < ARRAY_WIDTH - 1) && 
            // doesn't draw the parts if it's in the gap
                !(i > pipeYArray - PIPE_GAP && i < pipeYArray + PIPE_GAP))
            {
                // sets the correct positions to the PIPE_CHAR #
                screen[i][j] = PIPE_CHAR;
            }
        }
    }
}

// 0. takes the pipe as a parameter
// 1. moves the pipe to the left at a constant speed
// 2. if the pipe goes off the screen on the left move it back to the right
void updatePipe(Pipe* pipe)
{
    // add the pipes speed to its position
    pipe->pipeX += PIPE_SPEED;
    // checks if the pipe is off the screen to the left
    if(pipe->pipeX <= 0)
    {
        // in that case move it back to the right
        pipe->pipeX = SCREEN_WIDTH;
    }
}

// 0. takes the screen pointer as a parameter
// 1. clears the screen
// 2. declares variables for the message and the length
// 3. put the message on the screen
// 4. print the screen out
void drawStart(char screen[ARRAY_HEIGHT][ARRAY_WIDTH + 1])
{
    // clear the screen for a blank state
    clearScreen(screen);
    // initializes a string literal for the start message
    char *startMessage = "Press Space To Start";
    // initializes a variable for the length of the message
    int messageLength = strlen(startMessage);
    // loops through the length of the message
    for(int i = 0; i < messageLength; i++)
    {
        // centers the message to the center of the string
        screen[ARRAY_HEIGHT / 2][ARRAY_WIDTH / 2 - (messageLength / 2) + i] 
        = startMessage[i];
    }
    // print the screen out
    printScreen(screen);
}

// 0. takes the screen pointer as a parameter
// 1. clears the screen
// 2. declares variables for the message and the length
// 3. put the message on the screen
// 4. print the screen out
void drawDead(char screen[ARRAY_HEIGHT][ARRAY_WIDTH + 1])
{
    // clear the screen for a blank slate
    clearScreen(screen);
    // initializes a string literal for the start message
    char *deathMessage = "Press Space To Restart";
    // initializes a variable for the length of the message
    int messageLength = strlen(startMessage);
    // loops through the length of the message
    for(int i = 0; i < messageLength; i++)
    {
        // centers the message to the center of the string
        screen[ARRAY_HEIGHT / 2][ARRAY_WIDTH / 2 - (messageLength / 2) + i] 
        = deathMessage[i];
    }
    // print the screen out
    printScreen(screen);
}