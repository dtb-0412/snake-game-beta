#pragma once

// Constants
#define MAX_SIZE_SNAKE 10
#define MAX_SIZE_FOOD 4
#define MAX_SPEED 20

#include<windows.h>

// Global variables
POINT snake[10]; //snake
POINT food[4]; // food
int CHAR_LOCK; // used to determine the direction my snake cannot move (At a moment, there is one direction my snake cannot move to)
int MOVING; // used to determine the direction my snake moves (At a moment, there are three directions my snake can move)
int SPEED; // Standing for level, the higher the level, the quicker the speed
int HEIGH_CONSOLE, WIDTH_CONSOLE; // Width and height of console-screen
int FOOD_INDEX; // current food-index
int SIZE_SNAKE; // size of snake, initially maybe 6 units and maximum size may be 10
int STATE; // State of snake: dead or alive
