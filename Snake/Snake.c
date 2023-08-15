// Snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <stdbool.h>

#define MAX_LENGTH      50
#define BOARD_WIDTH     20
#define BOARD_HEIGHT    20

#define RIGHT           0
#define LEFT            1
#define UP              2
#define DOWN            3

#define FRUIT_SYMBOL    "*"
#define SNAKE_HEAD_SYM  "0"
#define SNAKE_BODY_SYM  "o"

void setup(void);
void input(void);
void draw(int height, int width);
void update(void);

int snakex[MAX_LENGTH], snakey[MAX_LENGTH];
int fruitx, fruity;
int snakelength = 0;

int direction = RIGHT;
int gameover = 0;

int score = 0;

int fruit_value;
int refresh_rate;
int difficulty;
char difficulty_name[7];

int main(void)
{
    srand(time(0));
    score = 0;

    snakex[0] = BOARD_WIDTH / 2;
    snakey[0] = BOARD_HEIGHT / 2;
    
    int uipt;
    printf("Welcome to snake! Please select difficulty from 1 to 3 (1 - Easy, 2 - Medium, 3 - Hard): ");
    scanf_s("%d", &uipt);

    if (uipt <= 1)
        difficulty = 1;
    else if (uipt >= 3)
        difficulty = 3;
    else
        difficulty = uipt;

    if (difficulty == 1) {
        refresh_rate = 250;
        fruit_value = 10;
        sprintf_s(difficulty_name, "Easy");
    }
    else if (difficulty == 2) {
        refresh_rate = 200;
        fruit_value = 20;
        sprintf_s(difficulty_name, "Medium");
    }
    else {
        refresh_rate = 125;
        fruit_value = 30;
        sprintf_s(difficulty_name, "Hard");
    }

    setup();
    while (!gameover) {    
        Sleep(refresh_rate);
        input();
        update();
        draw(BOARD_HEIGHT, BOARD_WIDTH);
    }
    return 0;
}

void draw(int height, int width)
{
    system("cls"); //Clear window
    int i = 0, j = 0;
    bool printedsnake;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            printedsnake = false;

            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
                printf("#");
            else if (i == fruity && j == fruitx)
                printf(FRUIT_SYMBOL);
            else if (i == snakey[0] && j == snakex[0])
                printf(SNAKE_HEAD_SYM);
            else {
                for (int s = 0; s <= snakelength; s++) {
                    if (i == snakey[s] && j == snakex[s]) {
                        printf(SNAKE_BODY_SYM);
                        printedsnake = true;
                    }
                }
                if (!printedsnake)
                    printf(" ");
            }
        }
        printf("\n");
    }
    printf("Score: %d (%s difficulty)\n", score, difficulty_name);
    printf("Press X to quit the game.\n");
}

bool checkcollision(void)
{
    for (int i = 0; i <= snakelength; i++) {
        if (fruitx == snakex[i] && fruity == snakey[i])
            return true;
    }

    return false;
}

void setup(void)
{
    do {
        fruitx = (rand() % BOARD_WIDTH) - 1;
        fruity = (rand() % BOARD_HEIGHT) - 1;
    } while ( checkcollision() || fruitx < 1 || fruity < 1 );
}

// Function to take the input
void input(void)
{
    if (_kbhit()) {
        switch (_getch()) {
        case 'a':
            if (direction != RIGHT)
                direction = LEFT;
            else
                direction = UP;
            break;
        case 's':
            if (direction != UP)
                direction = DOWN;
            else
                direction = RIGHT;
            break;
        case 'd':
            if (direction != LEFT)
                direction = RIGHT;
            else
                direction = UP;
            break;
        case 'w':
            if (direction != DOWN)
                direction = UP;
            else
                direction = RIGHT;
            break;
        case 'x':
            gameover = 1;
            break;
        }
    }
}

void update(void)
{
    int tmpx, tmpy;
    tmpx = snakex[0];
    tmpy = snakey[0];

    switch (direction) {
    case UP:
        tmpy--;
        break;
    case LEFT:
        tmpx--;
        break;
    case DOWN:
        tmpy++;
        break;
    case RIGHT:
        tmpx++;
        break;
    }

    for (int i = snakelength; i > 0; i--) {
        snakex[i] = snakex[i - 1];
        snakey[i] = snakey[i - 1];
    }

    snakex[0] = tmpx;
    snakey[0] = tmpy;

    if (snakex[0] >= BOARD_WIDTH - 1 || snakex[0] < 1 || snakey[0] >= BOARD_HEIGHT - 1 || snakey[0] < 1)
        gameover = 1;

    else {
        for (int i = 1; i <= snakelength; i++) {
            if (snakex[0] == snakex[i] && snakey[0] == snakey[i]) {
                gameover = 1;
                return;
            }
        }
        if (snakex[0] == fruitx && snakey[0] == fruity) {
            score += fruit_value;

            if (snakelength < MAX_LENGTH - 1 )
                snakelength++;

            setup();
        }
    }
}
