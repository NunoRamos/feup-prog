#include<Windows.h>
#include<iostream>
#include<string>

#include "AuxFunctions.h"
#include "Position.h"

using namespace std;

PositionInt ConvertToPositionInt(PositionChar position)
{
	PositionInt result;

	result.col = position.col - 97;
	result.lin = position.lin - 65;

	return result;
}


PositionChar ConvertToPositionChar(PositionInt position)
{
	PositionChar result;

	result.col = position.col + 97;
	result.lin = position.lin + 65;

	return result;
}

void WaitForEnter()
{
	string dummy;
	cout << "Press any key to continue . . .\n";
	cin.ignore(1000, '\n');
	getline(cin, dummy);
}

void ClearScreen()
{
	COORD coordScreen = { 0, 0 };
	unsigned long cCharsWritten;
	unsigned long dwConSize;
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(hCon, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	FillConsoleOutputCharacter(hCon, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hCon, &csbi);
	FillConsoleOutputAttribute(hCon, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);

	SetConsoleCursorPosition(hCon, coordScreen);

}

void SetColor(unsigned int color)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}
//==========================================================================================//

// Set text color & background

void SetColor(unsigned int color, unsigned int background_color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE); if (background_color == 0)
		SetConsoleTextAttribute(hCon, color); else
		SetConsoleTextAttribute(hCon, color | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
}