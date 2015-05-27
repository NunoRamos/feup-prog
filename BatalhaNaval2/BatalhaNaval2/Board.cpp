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
	Position<char> position;
	char orientation, line, column;
	unsigned int color;
	char dummy;

	boardFile.open(filename);

	boardFile >> numLines >> dummy >> numColumns;

	while (!boardFile.eof())
	{
		boardFile >> symbol >> size >> line >> column >> orientation >> color;
		position.line = line;
		position.column = column;
		ships.push_back(Ship(symbol, position, orientation, size, color));
	}

	boardFile.close();

	board.resize(numLines, vector<int>(numColumns, -1));

	for (size_t i = 0; i < ships.size(); i++)
	{
		PutShip(ships.at(i), i);
	}
}

//==========================================================================================//
//Can Place Ship
//Checks if a ship is placeable.
//Returns true if the ship can be placed. Returns false otherwise.


bool Board::CanPlaceShip(const Ship &s)
{

	if (s.GetShipOrientation() == 'V')
	{
		if (s.GetShipPosition().line + s.GetShipSize() > numLines - 1)
			return false;

		for (unsigned int i = 0; i < s.GetShipSize(); i++)
		{
			if (board.at(s.GetShipPosition().line + i).at(s.GetShipPosition().column) != -1)
				return false;
		}
	}
	else
	{
		if (s.GetShipPosition().column + s.GetShipSize() > numColumns - 1)
			return false;

		for (unsigned int i = 0; i < s.GetShipSize(); i++)
		{
			if (board.at(s.GetShipPosition().line).at(s.GetShipPosition().column + i) != -1)
				return false;
		}
	}

	return true;
}

//==========================================================================================//
//Put Ship
//Tries to put a ship in the "board" vector.
//Returns true if the ship has been placed. Returns false otherwise.


bool Board::PutShip(const Ship &s, int shipIndex) 
{
	Position<unsigned int> shipPosition = s.GetShipPosition();

	if (s.GetShipOrientation() == 'V')
	{
		//If the ship has already been destroyed, write -1.
		if (s.IsDestroyed())
		{
			for (unsigned int i = 0; i < s.GetShipSize(); i++)
			{
				board.at(shipPosition.line + i).at(shipPosition.column) = -1;
			}
			return false;
		}

		if (!CanPlaceShip(s))
			return false;

		//Adds the ship.
		for (unsigned int i = 0; i < s.GetShipSize(); i++)
		{
			board.at(shipPosition.line + i).at(shipPosition.column) = shipIndex;
		}
	}
	else
	{
		//If the ships has already been destroyed, write -1.
		if (s.IsDestroyed())
		{
			for (unsigned int i = 0; i < s.GetShipSize(); i++)
			{
				board.at(shipPosition.line).at(shipPosition.column + i) = -1;
			}
			return false;
		}

		if (!CanPlaceShip(s))
			return false;

		//Adds the ship.
		for (unsigned int i = 0; i < s.GetShipSize(); i++)
		{
			board.at(shipPosition.line).at(shipPosition.column + i) = shipIndex;
		}
	}

	return true;
}

//==========================================================================================//
//Remove Ship
//Removes the ship only from the board. Does not update its coordinates nor the "ships" vector.

void Board::RemoveShip(const Ship &s)
{
	Position<unsigned int> shipPosition = s.GetShipPosition();

	if (s.GetShipOrientation() == 'V')
	{
		for (unsigned int i = 0; i < s.GetShipSize(); i++)
		{
			board.at(shipPosition.line + i).at(shipPosition.column) = -1;
		}
	}
	else
	{
		for (unsigned int i = 0; i < s.GetShipSize(); i++)
		{
			board.at(shipPosition.line).at(shipPosition.column + i) = -1;
		}
	}
}

//==========================================================================================//
//Get Ships Area
//Calculates the area of the board occupied by all the ships.
//Returns the sum of all ships sizes.

unsigned int Board::GetShipsArea() const
{
	unsigned int sum = 0;

	for (size_t i = 0; i < ships.size(); i++)
	{
		sum += ships.at(i).GetShipSize();
	}

	return sum;
}

//==========================================================================================//
//Get Board Area
//Returns number of columns times number of lines.

unsigned int Board::GetBoardArea() const
{
	return numColumns*numLines;
}

//==========================================================================================//
//Move Ship
//Creates a copy of the original board, position and orientation. It then tries to move a ship randomly.
//If it cannot, the original configurations will be restored.
//Returns true if the ship has been moved. Returns false otherwise.

bool Board::MoveShip(unsigned int shipIndex)
{
	Position<unsigned int> originalPosition = ships.at(shipIndex).GetShipPosition();
	char originalOrientation = ships.at(shipIndex).GetShipOrientation();

	RemoveShip(ships.at(shipIndex));

	if (ships.at(shipIndex).MoveRand(0, 0, numLines - 1, numColumns - 1))
	{
		if (!PutShip(ships.at(shipIndex), shipIndex))
		{
			ships.at(shipIndex).SetShipPosition(originalPosition);
			ships.at(shipIndex).SetShipOrientation(originalOrientation);
			PutShip(ships.at(shipIndex), shipIndex);
			return false;
		}
	}
	else
	{
		ships.at(shipIndex).SetShipPosition(originalPosition);
		ships.at(shipIndex).SetShipOrientation(originalOrientation);
		PutShip(ships.at(shipIndex), shipIndex);
		return false;
	}

	return true;
}

//==========================================================================================//
//Get Ships Left
//Iterates through the "ships" vector and counts for every destroyed ship. Then, it returns the counter.
//Returns the number of ships left.

unsigned int Board::GetShipsLeft() const
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
		if (!ships.at(i).IsDestroyed())
			MoveShip(i);
	}
}

//==========================================================================================//
//Get Ship
//Returns the ship at "shipIndex" from "ships".

Ship Board::GetShip(unsigned int shipIndex) const 
{
	return ships.at(shipIndex);
}

//==========================================================================================//
//Get Ship
//Returns the number of columns.

unsigned int Board::GetColumns() const
{
	return numColumns;
}

//==========================================================================================//
//Get Ship
//Returns the number of lines.

unsigned int Board::GetLines() const
{
	return numLines;
}

//==========================================================================================//
//Attack
//Tries to attack a ship in the bomb's position.
//Returns the ship index if it hit a ship. Returns -1 otherwise.

int Board::Attack(Bomb &b)
{
	Position<unsigned int> bombPosition = ConvertToPositionUInt(b.GetTargetPosition());

	if (board.at(bombPosition.line).at(bombPosition.column) != -1)
	{
		int shipIndex = board.at(bombPosition.line).at(bombPosition.column);
		size_t i = 0;
		char orientation = ships.at(shipIndex).GetShipOrientation();

		Position<unsigned int> shipPosition = ships.at(shipIndex).GetShipPosition();

		if (orientation == 'H')
		{
			while (i < ships.at(shipIndex).GetShipSize())
			{
				if (shipPosition.column + i == bombPosition.column)
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
				if (shipPosition.line + i == bombPosition.line)
				{
					break;
				}
				i++;
			}
		}

		if (ships.at(board.at(bombPosition.line).at(bombPosition.column)).IsDestroyed())
			return -1;

		if (!ships.at(board.at(bombPosition.line).at(bombPosition.column)).Attack(i))
			return -2;
		else
			return shipIndex;
	}

	return -1;

}
