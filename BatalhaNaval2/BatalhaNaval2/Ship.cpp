#include "Ship.h"
#include "AuxFunctions.h"




Ship::Ship(char symbol, PositionChar position, char orientation, unsigned int size,
	unsigned int color)
{
	this->symbol = symbol;
	this->position = ConvertToPositionInt(position);
	this->orientation = orientation;
	this->size = size;
	this->color = color;
	lastPartDestroyed = -1;
	status = string(size, symbol);
}

int Ship::GetShipColor() const
{
	return color;
}

int Ship::GetLastPartDestroyed() const
{
	return lastPartDestroyed;
}

unsigned int Ship::GetShipSize() const
{
	return size;
}

PositionInt Ship::GetShipPosition() const
{
	return position;
}

char Ship::GetShipOrientation() const
{
	return orientation;
}

char Ship::GetShipSymbol() const
{
	return symbol;
}

string Ship::GetShipStatus() const
{
	return status;
}

char Ship::GetShipStatusSymbol(PositionInt position) const
{
	if (orientation == 'V')
		return status.at(position.lin - this->position.lin);
	else
		return status.at(position.col - this->position.col);
}

bool Ship::Move(char direction, bool rotate, unsigned int lineMin, unsigned int
	columnMin, unsigned int lineMax, unsigned int columnMax)
{
	return true;
}

bool Ship::MoveRand(unsigned int lineMin, unsigned int columnMin, unsigned int
	lineMax, unsigned int columnMax)
{
	PositionInt positionCopy;
	char orientationTemp = orientation;

	positionCopy.lin = position.lin;
	positionCopy.col = position.col;

	switch (rand() % 5)
	{
	case 0:
		break;
	case 1:
		positionCopy.col = position.col + 1;
		break;
	case 2:
		positionCopy.col = position.col - 1;
		break;
	case 3:
		positionCopy.lin = position.lin + 1;
		break;
	case 4:
		positionCopy.lin = position.lin - 1;
		break;
	}

	switch (rand() % 2)
	{
	case 0:
		break;
	case 1:
		if (orientation == 'H')
		{
			if (positionCopy.lin + size > lineMax)
				return false;
			else orientationTemp = 'V';
		}
		else if (orientation == 'V')
		{
			if (positionCopy.col + size > columnMax)
				return false;
			else orientationTemp = 'H';
		}

	}

	if (positionCopy.lin < lineMin || positionCopy.lin >= lineMax || positionCopy.col < columnMin || positionCopy.col >= columnMax)
		return false;

	orientation = orientationTemp;
	position.lin = positionCopy.lin;
	position.col = positionCopy.col;

	return true;
}

void Ship::SetShipOrientation(char orientation)
{
	this->orientation = orientation;
}

bool Ship::Attack(size_t partNumber)
{
	if (status.at(partNumber) == tolower(status.at(partNumber)))
		return false;
	else status.at(partNumber) = tolower(status.at(partNumber));

	lastPartDestroyed = partNumber;
	return true;
}

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

void Ship::SetShipPosition(PositionInt position)
{
	this->position = position;
}


