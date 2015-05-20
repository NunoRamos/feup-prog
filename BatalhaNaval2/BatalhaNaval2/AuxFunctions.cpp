#include<Windows.h>
#include<iostream>
#include<string>

#include "AuxFunctions.h"
#include "Position.h"

using namespace std;

//==========================================================================================//
//Convert To PositionInt
//Gets a PositionChar as argument and converts it to PositionInt.
//Returns a PositionInt.

PositionInt ConvertToPositionInt(PositionChar position)
{
	PositionInt result;

	result.col = position.col - 97;
	result.lin = position.lin - 65;

	return result;
}

//==========================================================================================//
//Convert To PositionChar
//Gets a PositionInt as argument and converts it to PositionChar.
//Returns a PositionChar.

PositionChar ConvertToPositionChar(PositionInt position)
{
	PositionChar result;

	result.col = position.col + 97;
	result.lin = position.lin + 65;

	return result;
}

//==========================================================================================//
//Wait For User Input
//Waits for the user to press a key.
//Returns nothing.

void WaitForUserInput()
{
	string dummy;
	cout << "Press any key to continue . . .\n";
	cin.get();
}

//==========================================================================================//
//Clear Screen
//Clears the console screen.
//Returns nothing.


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

//==========================================================================================//
//Set Color (overloaded)
//Sets text color according to its argument.
//Returns nothing.


void SetColor(unsigned int color)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}
//==========================================================================================//
//Set Color (overloaded)
//Sets text and background color according to its arguments.
//Returns nothing.

void SetColor(unsigned int color, unsigned int background_color)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE); if (background_color == 0)
		SetConsoleTextAttribute(hCon, color); else
		SetConsoleTextAttribute(hCon, color | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
}