/*
	Console.c: console-related functions
		This file is for Windows
*/



#include <stdio.h>
#include <stdlib.h>

#include "Console.h"

// #ifdef _WINDOWS
// for windows

#include <windows.h>

// #include "Console.h"

void Console::clrscr(void)		// clear the screen
{
	COORD Cur= {0, 0};
	unsigned long dwLen = 0;

	int width = getWindowWidth();
	int height = getWindowHeight();
	int size = width * height;

	gotoxy(1, 1);
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', size, Cur, &dwLen);
	gotoxy(1, 1);
}

void Console::gotoxy(int x, int y)	// move cursor to (x, y)
{
	COORD Pos = { (short)(x - 1), (short)(y - 1)};

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int Console::getWindowWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo (GetStdHandle (STD_OUTPUT_HANDLE), &csbi);

    return (int)(csbi.srWindow.Right - csbi.srWindow.Left + 1);
}

int Console::getWindowHeight()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo (GetStdHandle (STD_OUTPUT_HANDLE), &csbi);

    return (int)(csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
}

void Console::EnableCursor(int enable)
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = enable;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void Console::MySleep(int msec)
{
	Sleep(msec);
}

void Console::MyPause()
{
	system("PAUSE");
}

// #endif	// _WINDOWS



void Console::DrawLine(int x1, int y1, int x2, int y2, char c)
{
	int dx = 0, dy = 0;
	int x = 0, y = 0;

	if(abs(x2 - x1) > abs(y2 - y1)){
		if(x1 > x2){
			swap(&x1, &x2);
			swap(&y1, &y2);
		}
	} else if(y1 > y2){
		swap(&x1, &x2);
		swap(&y1, &y2);
	}

	dx = x2 - x1;
	dy = y2 - y1;

	if(dx >= dy){
		if(dx == 0){
			gotoxy(x1, y1);
			printf("%c", c);
		} else {
			for(x = x1; x <= x2; x++){
				y = (y1 * (x2 - x) + y2 * (x - x1) + dx / 2) / dx;
				gotoxy(x, y);
				printf("%c", c);
			}
		}
	} else {
		for(y = y1; y <= y2; y++){
			x = (x1 * (y2 - y) + x2 * (y - y1) + dy / 2) / dy;
			gotoxy(x, y);
			printf("%c", c);
		}
	}
}

void Console::swap(int *pa, int *pb)
{
	int temp = *pa;
	*pa = *pb;
	*pb = temp;
}

