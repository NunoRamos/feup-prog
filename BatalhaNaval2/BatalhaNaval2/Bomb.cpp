#include "Bomb.h"
#include "AuxFunctions.h"
#include <stdlib.h>     

//==========================================================================================//
//Bomb Constructor
//Tries to randomly change the bomb target.

Bomb::Bomb(PositionChar targetPosition)
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

	targetColumn = Minimum(targetColumn, 0);
	targetLine = Minimum(targetLine, 0);

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
