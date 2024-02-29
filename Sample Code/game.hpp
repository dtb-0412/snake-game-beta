#pragma once

#include<iostream>
#include<conio.h>
#include<ctime>
#include<thread>

#include"globals.hpp"

using namespace std;

void FixConsoleWindow() {
	// đoạn này xài winapi để tạo cửa sổ game, có trong thư viện <windows.h>, include bên "globals.hpp"
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void GotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

bool IsValid(int x, int y) {
	for (int i = 0; i < SIZE_SNAKE; i++) {
		if (snake[i].x == x && snake[i].y == y) {
			return false;
		}
		return true;
	}
}

void GenerateFood() {
	int x, y;
	srand(time(NULL));
	for (int i = 0; i < MAX_SIZE_FOOD; i++) {
		do {
			x = rand() % (WIDTH_CONSOLE - 1) + 1;
			y = rand() % (HEIGH_CONSOLE - 1) + 1;
		} while (IsValid(x, y) == false);
		food[i] = { x,y };
	}
}

void ResetData() {
	//Initialize the global values
	CHAR_LOCK = 'A', MOVING = 'D', SPEED = 8;

	// Initialize default values for snake
	FOOD_INDEX = 0, WIDTH_CONSOLE = 70, HEIGH_CONSOLE = 20, SIZE_SNAKE = 6;
	snake[0] = { 10, 5 }; snake[1] = { 11, 5 };
	snake[2] = { 12, 5 }; snake[3] = { 13, 5 };
	snake[4] = { 14, 5 }; snake[5] = { 15, 5 };
	GenerateFood(); //Create food array
}

void DrawBoard(int x, int y, int width, int height, int curPosX = 0, int curPosY = 0) {
	GotoXY(x, y); cout << 'X';

	for (int i = 1; i < width; i++) cout << 'X';
	cout << 'X';

	GotoXY(x, height + y); cout << 'X';

	for (int i = 1; i < width; i++) cout << 'X';
	cout << 'X';

	for (int i = y + 1; i < height + y; i++) {
		GotoXY(x, i); cout << 'X';
		GotoXY(x + width, i); cout << 'X';
	}

	GotoXY(curPosX, curPosY);
}

void StartGame() {
	system("cls");
	ResetData(); // Intialize original data
	DrawBoard(0, 0, WIDTH_CONSOLE, HEIGH_CONSOLE); // Draw game
	STATE = 1; // Start running Thread
}

//Function exit game
void ExitGame(HANDLE t) {
	system("cls");
	TerminateThread(t, 0);
}

//Function pause game
void PauseGame(HANDLE t) {
	SuspendThread(t);
}

//Function to update global data
void Eat() {
	snake[SIZE_SNAKE] = food[FOOD_INDEX];
	if (FOOD_INDEX == MAX_SIZE_FOOD - 1) {
		FOOD_INDEX = 0;
		SIZE_SNAKE = 6;
		// if (SPEED < MAX_SPEED) SPEED++;
		GenerateFood();
	} else {
		FOOD_INDEX++;
		SIZE_SNAKE++;
	}
}

//Function to process the dead of snake
void ProcessDead() {
	STATE = 0;
	GotoXY(0, HEIGH_CONSOLE + 2);
	cout << "Dead, type y to continue or anykey to exit";
}

//Function to draw
void DrawSnakeAndFood(const char* str) {
	GotoXY(food[FOOD_INDEX].x, food[FOOD_INDEX].y);
	cout << str;
	for (int i = 0; i < SIZE_SNAKE; i++) {
		GotoXY(snake[i].x, snake[i].y);
		cout << str;
	}
}

void MoveRight() {
	if (snake[SIZE_SNAKE - 1].x + 1 == WIDTH_CONSOLE) {
		ProcessDead();
	} else {
		if (snake[SIZE_SNAKE - 1].x + 1 == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y) {
			Eat();
		}

		for (int i = 0; i < SIZE_SNAKE - 1; i++) {
			snake[i].x = snake[i + 1].x;
			snake[i].y = snake[i + 1].y;
		}
		snake[SIZE_SNAKE - 1].x++;
	}
}

void MoveLeft() {
	if (snake[SIZE_SNAKE - 1].x - 1 == 0) {
		ProcessDead();
	} else {
		if (snake[SIZE_SNAKE - 1].x - 1 == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y == food[FOOD_INDEX].y) {
			Eat();
		}
		
		for (int i = 0; i < SIZE_SNAKE - 1; i++) {
			snake[i].x = snake[i + 1].x;
			snake[i].y = snake[i + 1].y;
		}
		snake[SIZE_SNAKE - 1].x--;
	}
}

void MoveDown() {
	if (snake[SIZE_SNAKE - 1].y + 1 == HEIGH_CONSOLE) {
		ProcessDead();
	} else {
		if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y + 1 == food[FOOD_INDEX].y) {
			Eat();
		}
		
		for (int i = 0; i < SIZE_SNAKE - 1; i++) {
			snake[i].x = snake[i + 1].x;
			snake[i].y = snake[i + 1].y;
		}
		snake[SIZE_SNAKE - 1].y++;
	}
}

void MoveUp() {
	if (snake[SIZE_SNAKE - 1].y - 1 == 0) {
		ProcessDead();
	} else {
		if (snake[SIZE_SNAKE - 1].x == food[FOOD_INDEX].x && snake[SIZE_SNAKE - 1].y - 1 == food[FOOD_INDEX].y) {
			Eat();
		}

		for (int i = 0; i < SIZE_SNAKE - 1; i++) {
			snake[i].x = snake[i + 1].x;
			snake[i].y = snake[i + 1].y;
		}
		snake[SIZE_SNAKE - 1].y--;
	}
}

//Subfunction for thread
void ThreadFunc() {
	while (1) {
		if (STATE == 1) {//If my snake is alive
			DrawSnakeAndFood(" ");

			switch (MOVING) {
				case 'A':
					MoveLeft();
					break;
				case 'D':
					MoveRight();
					break;
				case 'W':
					MoveUp();
					break;
				case 'S':
					MoveDown();
					break;
			}

			DrawSnakeAndFood("O");
			Sleep(1000 / SPEED); // Sleep function with SPEEED variable
		}
	}
}