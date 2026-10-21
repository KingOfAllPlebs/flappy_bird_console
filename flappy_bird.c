// header file
#include "flappy_bird.h"

// FUNCTION DEFINITIONS ///////////////////////////////////////////////////////

// 0. takes the screen pointer as a parameter
// 0. takes the bird as a parameter
// 0. takes the pipe as a parameter
// 1. seeds the random number generator
// 2. makes sure the screen is blank to start
// 3. sets the initial values for the bird
// 4. sets the initial values for the pipe
void initializeGame(char screen[ARRAY_HEIGHT][ARRAY_WIDTH + 1], Bird* bird, 
    Pipe* pipe, gameState* currentState)
{
    // seed the random number generator
    srand(time(NULL));
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

// SCREEN FUNCTIONS ///////////////////////////////////////////////////////////

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
// 1. clears the screen
// 2. draws the bird
// 3. checks if there is a message and title to be displayed
// 4. if so, display the title and message
// 5. prints the updated screen
void updateScreen(char screen[ARRAY_HEIGHT][ARRAY_WIDTH + 1], Bird bird, 
    Pipe pipe, const char* title, const char* message)
{
    // clear the screen back to it beingonly the border
    clearScreen(screen);
    // draw the pipe onto the screen
    drawPipe(screen, pipe);
    // draw the bird onto the screen
    drawBird(screen, bird);
    // if there is a title and message to be drawn
    if(strlen(title) != 0 && strlen(message) != 0)
    {
        // draw the title and message onto the screen
        drawTitleMessage(screen, title, message);
    }
    // print out the screen after all the previous edits
    printScreen(screen);
}

// 0. takes the screen pointer as a parameter
// 0. takes a string for the title and the message as a parameter
// 1. initializes the length of both strings
// 2. draws out the title at the first third
// 3. draws out the message at the second third
void drawTitleMessage(char screen[ARRAY_HEIGHT][ARRAY_WIDTH + 1], 
    const char* title, const char* message)
{
    // initializes a variable for the length of the title
    int titleLength = strlen(title);
    // initializes a variable for the length of the message
    int messageLength = strlen(message);
    // loops through the length of the title
    for(int i = 0; i < titleLength; i++)
    {
        // loop to put a border around the title
        for(int j = 0; j < 3; j++)
        {
            // checks if it's at the top or bottom of the title
            if(j == 0 || j == 2)
            {
                // put the borders at the top and bottom of the title
                screen[ARRAY_HEIGHT / 3 - 1 + j]
                [ARRAY_WIDTH / 2 - (titleLength / 2) + i] 
                = TITLE_CHAR;
            }
            else
            {
                // put the title message in between the borders
                screen[ARRAY_HEIGHT / 3 - 1 + j]
                [ARRAY_WIDTH / 2 - (titleLength / 2) + i] 
                = title[i];
            }
        }
    }
    // loops through the length of the message
    for(int i = 0; i < messageLength; i++)
    {
        // centers the message to the center of the string
        screen[(ARRAY_HEIGHT / 3) * 2]
        [ARRAY_WIDTH / 2 - (messageLength / 2) + i] 
        = message[i];
    }
}

// BIRD FUNCTIONS /////////////////////////////////////////////////////////////

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
}

// PIPE FUNCTIONS /////////////////////////////////////////////////////////////

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
        // move the pipes center to a new random positoin
        pipe->pipeY = (rand() % (MAX_PIPE_Y - MIN_PIPE_Y + 1)) + MIN_PIPE_Y;
        // in that case move it back to the right
        pipe->pipeX = SCREEN_WIDTH;
    }
}

// COLLISION FUNCTIONS ////////////////////////////////////////////////////////

// 0. takes the bird in as a parameter
// 1. checks if the bird would be above the screen
// 2. if so set the bird's y to the top to avoid overflow and return true
// 3. checks if the bird would be below the screen
// 4. if so set the bird's y to the bottom to avoid overflow and return true
// 5. otherwise return false
bool checkFloorCollision(Bird* bird)
{
    // checks if the bird would be above the screen
    if(bird->birdY < 0 + ARRAY_TO_SCREEN)
    {
        // keep the bird at the top
        bird->birdY = 0 + ARRAY_TO_SCREEN;
        // the bird is touching the ceiling
        return true;
    }
    // checks if the bird would be below the screen
    else if(bird->birdY > SCREEN_HEIGHT - ARRAY_TO_SCREEN * 2)
    {
        // keep the bird at the bottom
        bird->birdY = SCREEN_HEIGHT - ARRAY_TO_SCREEN * 2;
        // the bird is touching the floor
        return true;
    }
    // any other case
    else
    {
        // the bird is in bounds
        return false;
    }
}

// 0. takes the bird as a parameter
// 0. takes the pipe as a parameter
// 1. checks if the bird is within the y range of the pipes
// 1. chekcs if the bird is within the x range of the pipes
// 2. if it's within range return true
// 3. otherwise return false
bool checkPipeCollision(Bird* bird, Pipe pipe)
{   
    // check if the bird is in the y range of the pipes
    if((bird->birdY < pipe.pipeY - PIPE_GAP * ARRAY_TO_SCREEN ||
        bird->birdY > pipe.pipeY + PIPE_GAP * ARRAY_TO_SCREEN ) &&
    // check if the bird is in the x range of the pipes
        (bird->birdX < pipe.pipeX + (PIPE_WIDTH - 2) * ARRAY_TO_SCREEN &&
        bird->birdX > pipe.pipeX - (PIPE_WIDTH + 2) * ARRAY_TO_SCREEN))
    {
        // returns true if the bird is over the pipe
        return true;
    }
    // if the bird is not within the pipe
    else
    {
        // returns false
        return false;
    }
}

// INPUT FUNCTIONS ////////////////////////////////////////////////////////////

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