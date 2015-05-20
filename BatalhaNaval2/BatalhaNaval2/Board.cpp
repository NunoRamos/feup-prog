#include "Board.h"
#include "AuxFunctions.h"

#include<fstream>
#include<string>
#include<cctype>
#include<iostream>
#include<vector>

using namespace std;

//==========================================================================================//
//Board Default Constructor

Board::Board()
{

}

//==========================================================================================//
//Board Constructor
//Fills the "ships" vector with data read from "filename". Fills the "board" vector with data from "ships".

Board::Board(const string &filename)
{
	ifstream boardFile;

	char symbol;
	unsigned int size;
	PositionChar position;
	char orientation;
	unsigned int color;
	char dummy;

	boardFile.open(filename);

	boardFile >> numLines >> dummy >> numColumns;

	while (!boardFile.eof())
	{
		boardFile >> symbol >> size >> position.lin >> position.col >> orientation >> color;
		ships.push_back(Ship(symbol, position, orientation, size, color));
	}

	boardFile.close();

	board.resize(numLines, vector<int>(numColumns, -1));

	Update();
}

//==========================================================================================//
//Can Place Ship
//Checks if a ship is placeable.
//Returns true if the ship can be placed. Returns false otherwise.


bool Board::CanPlaceShip(const Ship &s)
{
	if (s.GetShipOrientation() == 'V')
	{
		//Verifica se dá para acrescentar o navio
		for (unsigned int i = 0; i < s.GetShipSize(); i++)
		{
			if (board.at(s.GetShipPosition().lin + i).at(s.GetShipPosition().col) != -1)
				return false;
		}
	}
	else
	{
		//Verifica se dá para acrescentar o navio
		for (unsigned int i = 0; i < s.GetShipSize(); i++)
		{
			if (board.at(s.GetShipPosition().lin).at(s.GetShipPosition().col + i) != -1)
				return false;
		}
	}
}

//==========================================================================================//
//Put Ship
//Tries to put a ship in the "board" vector.
//Returns true if the ship has been placed. Returns false otherwise.


bool Board::PutShip(const Ship &s, int shipIndex) 
{
	PositionInt shipPosition = s.GetShipPosition();

	if (s.GetShipOrientation() == 'V')
	{
		//If the ship has already been destroyed, write -1.
		if (s.IsDestroyed())
		{
			for (unsigned int i = 0; i < s.GetShipSize(); i++)
			{
				board.at(shipPosition.lin + i).at(shipPosition.col) = -1;
			}
		}

		if (!CanPlaceShip(s))
			return false;

		//Adds the ship.
		for (unsigned int i = 0; i < s.GetShipSize(); i++)
		{
			board.at(shipPosition.lin + i).at(shipPosition.col) = shipIndex;
		}
	}
	else
	{
		//If the ships has already been destroyed, write -1.
		if (s.IsDestroyed())
		{
			for (unsigned int i = 0; i < s.GetShipSize(); i++)
			{
				board.at(shipPosition.lin).at(shipPosition.col + i) = -1;
			}
		}

		if (!CanPlaceShip(s))
			return false;

		//Adds the ship.
		for (unsigned int i = 0; i < s.GetShipSize(); i++)
		{
			board.at(shipPosition.lin).at(shipPosition.col + i) = shipIndex;
		}
	}

	return true;
}

//==========================================================================================//
//Remove Ship
//Removes the ship only from the board. Does not update its coordinates nor the "ships" vector.

void Board::RemoveShip(const Ship &s)
{
	PositionInt shipPosition = s.GetShipPosition();

	if (s.GetShipOrientation() == 'V')
	{
		for (unsigned int i = 0; i < s.GetShipSize(); i++)
		{
			board.at(shipPosition.lin + i).at(shipPosition.col) = -1;
		}
	}
	else
	{
		for (unsigned int i = 0; i < s.GetShipSize(); i++)
		{
			board.at(shipPosition.lin).at(shipPosition.col + i) = -1;
		}
	}
}

//==========================================================================================//
//Move Ship
//Creates a copy of the original board, position and orientation. It then tries to move a ship randomly.
//If it cannot, the original configurations will be restored.
//Returns true if the ship has been moved. Returns false otherwise.

bool Board::MoveShip(unsigned int shipIndex)
{
	vector<vector<int>> originalBoard = board;
	PositionInt originalPosition = ships.at(shipIndex).GetShipPosition();
	char originalOrientation = ships.at(shipIndex).GetShipOrientation();
	bool placeInOldPosition = false;

	RemoveShip(ships.at(shipIndex));

	if (ships.at(shipIndex).MoveRand(0, 0, numLines - 1, numColumns - 1))
	{
		if (!PutShip(ships.at(shipIndex), shipIndex))
		{
			placeInOldPosition = true;
		}
	}
	else
		placeInOldPosition = true;

	if (placeInOldPosition)
	{
		board = originalBoard;
		ships.at(shipIndex).SetShipPosition(originalPosition);
		ships.at(shipIndex).SetShipOrientation(originalOrientation);
		return false;
	}

	return true;
}

//==========================================================================================//
//Get Ships Left
//Iterates through the "ships" vector and counts for every destroyed ship. Then, it returns the counter.
//Returns the number of ships left.

unsigned int Board::GetShipsLeft()
{
	unsigned int shipsInVector = ships.size();
	unsigned int destroyedShips = 0;

	for (size_t i = 0; i < ships.size(); i++)
	{
		if (ships.at(i).IsDestroyed())
			destroyedShips++;
	}

	return shipsInVector - destroyedShips;
}

//==========================================================================================//
//Move Ships
//Attempts to move every ship of the "ships" vector using the function MoveShip.

void Board::MoveShips()
{
	for (size_t i = 0; i < ships.size(); i++)
	{
		MoveShip(i);
	}
}

//==========================================================================================//
//Get Ship
//Returns the ship at "shipIndex" from "ships".

Ship Board::GetShip(unsigned int shipIndex)
{
	return ships.at(shipIndex);
}

//==========================================================================================//
//Attack
//Tries to attack a ship in the bomb's position.
//Returns the ship index if it hit a ship. Returns -1 otherwise.

int Board::Attack(const Bomb &b)
{
	PositionInt bombPosition = ConvertToPositionInt(b.GetTargetPosition());

	if (bombPosition.col > numColumns || bombPosition.lin > numLines)
		return -1;

	if (board.at(bombPosition.lin).at(bombPosition.col) != -1)
	{

		int shipIndex = board.at(bombPosition.lin).at(bombPosition.col);
		size_t i = 0;
		char orientation = ships.at(shipIndex).GetShipOrientation();

		PositionInt shipPosition = ships.at(shipIndex).GetShipPosition();

		if (orientation == 'H')
		{
			while (i < ships.at(shipIndex).GetShipSize())
			{
				if (shipPosition.col + i == bombPosition.col)
				{
					break;
				}
				i++;
			}
		}
		else
		{
			while (i < ships.at(shipIndex).GetShipSize())
			{
				if (shipPosition.lin + i == bombPosition.lin)
				{
					break;
				}
				i++;
			}
		}

		if (ships.at(board.at(bombPosition.lin).at(bombPosition.col)).IsDestroyed())
			return -1;

		ships.at(board.at(bombPosition.lin).at(bombPosition.col)).Attack(i);

		return shipIndex;
	}

	return -1;

}

//==========================================================================================//
//Update
//Recreates the "board" vector and places every ship.

void Board::Update()
{
	board = vector<vector<int>>(numLines, vector<int>(numColumns, -1));

	for (size_t i = 0; i < ships.size(); i++)
	{
		PutShip(ships.at(i), i);
	}
}

//==========================================================================================//
//Display
//Prints the board to the screen.

void Board::Display() const
{

	cout << "  ";
	SetColor(15);
	for (unsigned int i = 0; i < board.at(0).size(); i++)	//	Creates the decapitalized letter row on the top of the board.
	{														
		cout << ' ' << (char)(97 + i);						
	}														
	cout << endl;


	for (unsigned int i = 0; i < board.size(); i++)
	{
		SetColor(15);
		cout << ' ' << (char)(65 + i);		//Adds the capitalized letter column to the left of the board.

		for (unsigned int j = 0; j < board.at(0).size(); j++)
		{
			if (board.at(i).at(j) == -1 || ships.at(board.at(i).at(j)).IsDestroyed())
			{
				SetColor(15, 4);
				cout << ' ' << '.';
			}
			else
			{
				PositionInt position;
				position.col = j;
				position.lin = i;
				SetColor(ships.at(board.at(i).at(j)).GetShipColor(), 4);
				cout << ' ' << ships.at(board.at(i).at(j)).GetShipStatusSymbol(position);
			}

		}
		cout << endl;
	}
	SetColor(15);
	cout << endl;

}
