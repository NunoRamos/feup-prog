#include<Windows.h>
#include<iostream>
#include<string>

#include "AuxFunctions.h"
#include "Position.h"
#include "Player.h"

using namespace std;

//==========================================================================================//
//Convert To Position<unsigned tnt>
//Gets a Position<char> as argument and converts it to Position<unsigned int>.
//Returns a PositionInt.

Position<unsigned int> ConvertToPositionUInt(Position<char> position)
{
	Position<unsigned int> result;

	result.SetColumn(position.GetColumn() - 97);
	result.SetLine(position.GetLine() - 65);

	return result;
}

//==========================================================================================//
//Convert To PositionChar
//Gets a PositionInt as argument and converts it to PositionChar.
//Returns a PositionChar.

Position<char> ConvertToPositionChar(Position<unsigned int> position)
{
	Position<char> result;

	result.SetColumn(position.GetColumn() + 97);
	result.SetLine(position.GetLine() + 65);

	return result;
}

//==========================================================================================//
//Operator << (Overloaded)
//Prints board.

ostream& operator<<(ostream& out, Board &board)
{
	out << "  ";
	SetColor(15);
	for (unsigned int i = 0; i < board.board.at(0).size(); i++)	//	Creates the decapitalized letter row on the top of the board.
	{
		out << ' ' << (char)(97 + i);
	}
	out << endl;


	for (unsigned int i = 0; i < board.numLines; i++)
	{
		SetColor(15);
		out << ' ' << (char)(65 + i);		//Adds the capitalized letter column to the left of the board.

		for (unsigned int j = 0; j < board.numColumns; j++)
		{
			if (board.board.at(i).at(j) == -1 || board.ships.at(board.board.at(i).at(j)).IsDestroyed())
			{
				SetColor(15, 4);
				out << ' ' << '.';
			}
			else
			{
				Position<unsigned int> position;
				position.SetColumn(j);
				position.SetLine(i);
				SetColor(board.ships.at(board.board.at(i).at(j)).GetShipColor(), 4);
				out << ' ' << board.ships.at(board.board.at(i).at(j)).GetShipStatusSymbol(position);
			}

		}
		out << endl;
	}
	SetColor(15);
	out << endl;

	return out;
}

//==========================================================================================//
//Operator << (Overloaded)
//Allows to print player.board.

ostream& operator<<(ostream& out, Player &player)
{
	out << player.board;
		return out;
}

//==========================================================================================//
//Wait For User Input
//Waits for the user to press a key.
//Returns nothing.

void WaitForUserInput()
{
	string dummy;
	std::cout << "Press enter to continue . . .\n";
	cin.ignore(1000, '\n');
	getline(cin, dummy);
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



//==========================================================================================//
//Maximum
//Returns the greatest number between n1 and n2.

int Maximum(int n1, int n2)
{
	if (n1 > n2)
		return n1;
	else
		return n2;
}

//==========================================================================================//
//Minimum
//Returns the smallest number between n1 and n2.

int Minimum(int n1, int n2)
{
	if (n1 < n2)
		return n1;
	else
		return n2;
}

void NormalizeTargetString(std::string &targetString)
{
	targetString.resize(2);

	if (targetString.at(0) >= 'a' && targetString.at(0) <= 'z')
		targetString.at(0) = targetString.at(0) - 32;
	if (targetString.at(1) >= 'A' && targetString.at(1) <= 'Z')
		targetString.at(1) = targetString.at(1) + 32;
}