#include "Bomb.h"
#include "AuxFunctions.h"
#include <stdlib.h>     

//==========================================================================================//
//Bomb Constructor
//Tries to randomly change the bomb target.

Bomb::Bomb(PositionChar targetPosition, unsigned int maxLines, unsigned int maxColumns)
{
	
	switch (rand() % 5)
	{
	case 0:
		targetColumn = targetPosition.col;
		targetLine = targetPosition.lin;
		break;
	case 1:
		targetColumn = targetPosition.col + 1;
		targetLine = targetPosition.lin;
		break;
	case 2:
		targetColumn = targetPosition.col - 1;
		targetLine = targetPosition.lin;
		break;
	case 3:
		targetColumn = targetPosition.col;
		targetLine = targetPosition.lin + 1;
		break;
	case 4:
		targetColumn = targetPosition.col;
		targetLine = targetPosition.lin - 1;
		break;
	}

	targetColumn = Maximum(targetColumn, 0);
	targetLine = Maximum(targetLine, 0);
	targetColumn = Minimum(targetColumn, maxColumns);
	targetLine = Minimum(targetLine, maxLines);
	
}

//==========================================================================================//
//Get Target Position
//Returns the bomb target as PositionChar.

PositionChar Bomb::GetTargetPosition() const
{
	PositionChar Target;
	Target.lin = targetLine;
	Target.col = targetColumn;
	return Target;
}
