#include "Ship.h"
#include "AuxFunctions.h"

//==========================================================================================//
//Ship Constructor
//Sets ship's attributes according to the arguments.

Ship::Ship(char symbol, Position<char> position, char orientation, unsigned int size,
	unsigned int color)
{
	this->symbol = symbol;
	this->position = ConvertToPositionUInt(position);
	this->orientation = orientation;
	this->size = size;
	this->color = color;
	lastPartDestroyed = -1;
	status = string(size, symbol);
}

//==========================================================================================//
//Get Ship Color
//Returns the ship color.

int Ship::GetShipColor() const
{
	return color;
}

//==========================================================================================//
//Get Last Part Destroyed
//Returns the index of the part that was last destroyed.

int Ship::GetLastPartDestroyed() const
{
	return lastPartDestroyed;
}

//==========================================================================================//
//Get Ship Size
//Returns the ship size.

unsigned int Ship::GetShipSize() const
{
	return size;
}

//==========================================================================================//
//Get Ship Position
//Returns the ship position as PositionInt

Position<unsigned int> Ship::GetShipPosition() const
{
	return position;
}

//==========================================================================================//
//Get Ship Orientation
//Returns the ship orientation.

char Ship::GetShipOrientation() const
{
	return orientation;
}

//==========================================================================================//
//Get Ship Symbol
//Returns the ship symbol.

char Ship::GetShipSymbol() const
{
	return symbol;
}

//==========================================================================================//
//Get Ship Status
//Returns the ship status.

string Ship::GetShipStatus() const
{
	return status;
}

//==========================================================================================//
//Get Ship Status Symbol
//Returns the ship capitalized or decapitalizeed symbol based on the ship status.

char Ship::GetShipStatusSymbol(Position<unsigned int> position)
{
	if (orientation == 'V')
		return status.at(position.line - this->position.line);
	else
		return status.at(position.column - this->position.column);
}

//==========================================================================================//
//Move Rand
//Tries to randomly move the ship.
//Returns true if the ship fits the board dimensions. Returns false otherwise.

bool Ship::MoveRand(unsigned int lineMin, unsigned int columnMin, unsigned int
	lineMax, unsigned int columnMax)
{
	Position<unsigned int> positionTemp;
	positionTemp.line = position.line;
	positionTemp.column = position.column;
	char orientationTemp = orientation;

	if (rand() % 2 == 1)
	{
		if (orientation == 'H')
		{
			if (!positionTemp.line + size > lineMax)
				orientationTemp = 'V';

		}
		else if (orientation == 'V')
		{
			if (!positionTemp.column + size > columnMax)
				orientationTemp = 'H';
		}

	}

	switch (rand() % 5)
	{
	case 0:
		break;
	case 1:
		positionTemp.column = position.column + 1;
		break;
	case 2:
		positionTemp.column = position.column - 1;
		break;
	case 3:
		positionTemp.line = position.line + 1;
		break;
	case 4:
		positionTemp.line = position.line - 1;
		break;
	}


	if (positionTemp.line < lineMin || positionTemp.line > lineMax || positionTemp.column < columnMin || positionTemp.column > columnMax)
		return false;

	position.line = positionTemp.line;
	position.column = positionTemp.column;
	orientation = orientationTemp;

	return true;
}

//==========================================================================================//
//Set Ship Orientation
//Sets the ship orientation according to its argument.

void Ship::SetShipOrientation(char orientation)
{
	this->orientation = orientation;
}

//==========================================================================================//
//Attack
//Changes the status of the ship depending on the attack and updates "lastPartDestroyed" attribute.
//Returns true if the ship part was changed. Returns false otherwise.

bool Ship::Attack(size_t partNumber)
{
	if (status.at(partNumber) == tolower(status.at(partNumber)))
		return false;
	else status.at(partNumber) = tolower(status.at(partNumber));

	lastPartDestroyed = partNumber;
	return true;
}

//==========================================================================================//
//Is Destroyed
//Checks if at least half of the ship status is decapitalized.
//Returns true if the condition above was met. Returns false otherwise.

bool Ship::IsDestroyed() const
{
	double numOfHits = 0;

	for (int i = 0; i < status.size(); i++)
	{
		if (status.at(i) == tolower(status.at(i)))
			numOfHits++;
	}
	if (numOfHits >= (double)status.size() / 2)
		return true;
	return false;
}

//==========================================================================================//
//Set Ship Position
//Sets the ship position according to its argument.

void Ship::SetShipPosition(Position<unsigned int> position)
{
	this->position = position;
}


