#include <stdio.h>
#include <windows.h>

#define ARRAY_HEIGHT 24
#define ARRAY_WIDTH 80

void initializeGame(char screen[ARRAY_HEIGHT][ARRAY_WIDTH + 1], float* birdX, float* birdY);
void clearScreen(char screen[ARRAY_HEIGHT][ARRAY_WIDTH + 1]);
void printScreen(const char screen[ARRAY_HEIGHT][ARRAY_WIDTH + 1]);
void drawBird(char screen[ARRAY_HEIGHT][ARRAY_WIDTH + 1], float birdX, float birdY);

int main()
{
    printf("\e[1;1H\e[2J");

    char screen[ARRAY_HEIGHT][ARRAY_WIDTH + 1];
    float birdX, birdY, birdVelocity;

    initializeGame(screen, &birdX, &birdY);

    for(int i = 0; i < 20; i++)
    {
        clearScreen(screen);
        drawBird(screen, birdX, birdY);
        printScreen(screen);
        Sleep(400);
    }

    return 0;
}

void initializeGame(char screen[ARRAY_HEIGHT][ARRAY_WIDTH + 1], float* birdX, float* birdY)
{
    clearScreen(screen);
    *birdX = 160;
    *birdY = 160;
}

void clearScreen(char screen[ARRAY_HEIGHT][ARRAY_WIDTH + 1])
{
    printf("\e[1;1H\e[2J");

    for(int i = 0; i < ARRAY_HEIGHT; i++)
    {
        for(int j = 0; j < ARRAY_WIDTH; j++)
        {
            if(i == 0 || i == ARRAY_HEIGHT - 1)
            {
                screen[i][j] = '#';
            }
            else if(j == 0 || j == ARRAY_WIDTH - 1)
            {
                screen[i][j] = '#';
            }
            else
            {
                screen[i][j] = ' ';
            }
        }
        screen[i][ARRAY_WIDTH] = '\0';
    }
}

void printScreen(const char screen[ARRAY_HEIGHT][ARRAY_WIDTH + 1])
{
    for(int i = 0; i < ARRAY_HEIGHT; i++)
    {
        printf("%s\n", screen[i]);
    }
}

void drawBird(char screen[ARRAY_HEIGHT][ARRAY_WIDTH + 1], float birdX, float birdY)
{
    int birdXArray = birdX * 0.0625;
    int birdYArray = birdY * 0.0625;

    for(int i = birdXArray - 1; i <= birdXArray + 1; i++)
    {
        for(int j = birdYArray - 1; j <= birdYArray + 1; j++)
        {
            screen[j][i] = '@';
        }
    }
}