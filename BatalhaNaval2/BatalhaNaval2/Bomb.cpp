#include "Bomb.h"
#include "AuxFunctions.h"
#include <stdlib.h>     

//==========================================================================================//
//Bomb Constructor
//Tries to randomly change the bomb target.

Bomb::Bomb(Position<char> targetPosition, unsigned int maxLines, unsigned int maxColumns)
{
	
	switch (rand() % 5)
	{
	case 1:
		targetPosition.column = targetPosition.column + 1;
		targetPosition.line = targetPosition.line;
		break;
	case 2:
		targetPosition.column = targetPosition.column - 1;
		targetPosition.line = targetPosition.line;
		break;
	case 3:
		targetPosition.column = targetPosition.column;
		targetPosition.line = targetPosition.line + 1;
		break;
	case 4:
		targetPosition.column = targetPosition.column;
		targetPosition.line = targetPosition.line - 1;
		break;
	}

	targetPosition.column = Maximum(targetPosition.column, 'a');
	targetPosition.line = Maximum(targetPosition.line, 'A');
	targetPosition.column = Minimum(targetPosition.column, maxColumns + 'a' - 1);
	targetPosition.line = Minimum(targetPosition.line, maxLines + 'A' - 1);
	
	target = targetPosition;
}

//==========================================================================================//
//Get Target Position
//Returns the bomb target as PositionChar.

Position<char> Bomb::GetTargetPosition()
{
	Position<char> target;
	target.line = this->target.line;
	target.column = this->target.column;
	return target;
}
