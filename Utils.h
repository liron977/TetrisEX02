#ifndef __UTILS_H_
#define __UTILS_H_
#include <iostream>
using namespace std;
#include <windows.h>
#include <conio.h>
#include <process.h>
#include "Color.h"


// function definition -- requires windows.h
inline void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}
inline void removeCursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = false;
	SetConsoleCursorInfo(consoleHandle, &info);
}
// function definition -- requires process.h
inline void clrscr()
{
	system("cls");
}
inline void setTextColor(Color colorToSet) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)colorToSet);
}

#endif