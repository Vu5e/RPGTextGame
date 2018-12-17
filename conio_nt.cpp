/*
	Console Input/Output written by Nicholas Tan.
	Last update : 14/11/2016
	conio_nt : version 1.0.1
*/

#include "conio_nt.h"


void SetFontColor(COLOR color)
{
	foregroundColor = color;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color + (backgroundColor << 4));
}

void SetBackgroundColor(COLOR color)
{
	backgroundColor = color;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), foregroundColor + (color << 4));
}

void GoToXY(int x, int y)
{
	COORD coordinate;

	coordinate.X = x - 1;
	coordinate.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

int GetCursorPositionX()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

	return info.dwCursorPosition.X + 1;
}

int GetCursorPositionY()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

	return info.dwCursorPosition.Y + 1;
}

void SetCursorType(int type)
{
	CONSOLE_CURSOR_INFO info;
	info.dwSize = type;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void HideCursor()
{
	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void ShowCursor()
{
	CONSOLE_CURSOR_INFO info;
	info.bVisible = true;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

void ClrScreen()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	DWORD consoleSize;
	DWORD written;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	consoleSize = info.dwSize.X * info.dwSize.Y;
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', consoleSize, { 0,0 }, &written);
	FillConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE), info.wAttributes, consoleSize, { 0,0 }, &written);
	GoToXY(1, 1);
}

void ClrLine()
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	COORD coordinate;
	DWORD written;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	coordinate.X = info.dwCursorPosition.X;
	coordinate.Y = info.dwCursorPosition.Y;
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', info.dwSize.X * info.dwCursorPosition.Y, coordinate, &written);
	GoToXY(info.dwCursorPosition.X + 1, info.dwCursorPosition.Y + 1);
}

void SetDisplayMode(int mode)
{
	COORD coordinate;
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), 2, &coordinate);
}

void SetWindowSize(short width, short height)
{
	SMALL_RECT windowSize;
	COORD largestSize;

	largestSize = GetLargestConsoleWindowSize(GetStdHandle(STD_OUTPUT_HANDLE));

	if (largestSize.X < width) width = largestSize.X - 2;
	if (largestSize.Y < height) height = largestSize.Y - 2;

	windowSize.Left = 0;
	windowSize.Top = 0;
	windowSize.Right = width - 1;
	windowSize.Bottom = height - 1;

	if (!SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), { width, height })) OutputDebugString("Failed to set screen buffer size");
	else OutputDebugString("Buffer Size Success");

	if(!SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize)) OutputDebugString("Failed to set window size");
	else OutputDebugString("Window Size Success");

}