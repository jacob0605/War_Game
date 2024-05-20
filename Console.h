/*
	Console.h: declarations for console-related functions
*/

#ifndef	__CONSOL__
#define	__CONSOL__

#ifdef	_WINDOWS
	#include <windows.h>
	#include <conio.h>
#endif	//	_WINDOWS

// void clrscr(void);              // clear screen
// void gotoxy(int x, int y);     // move cursor to (x, y) coordinate

// int getWindowWidth();       // get width of current console window
// int getWindowHeight();      // get height of current console window

// void DrawLine(int x1, int y1, int x2, int y2, char c);
// void swap(int *pa, int *pb);

// void EnableCursor(int enable);

// void MySleep(int msec);		// wait for msec milliseconds
// void MyPause();				// wait for the Enter key

class Console {
public:
	static void clrscr(void);
	static void gotoxy(int x, int y);
	static int getWindowWidth();
	static int getWindowHeight();
	static void DrawLine(int x1, int y1, int x2, int y2, char c);
	static void swap(int *pa, int *pb);
	static void EnableCursor(int enable);
	static void MySleep(int msec);
	static void MyPause();
};

#endif	//	__CONSOL__

