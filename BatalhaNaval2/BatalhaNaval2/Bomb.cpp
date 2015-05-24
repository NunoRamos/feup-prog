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
		targetPosition.SetColumn(targetPosition.GetColumn() + 1);
		targetPosition.SetLine(targetPosition.GetLine());
		break;
	case 2:
		targetPosition.SetColumn(targetPosition.GetColumn() - 1);
		targetPosition.SetLine(targetPosition.GetLine());
		break;
	case 3:
		targetPosition.SetColumn(targetPosition.GetColumn());
		targetPosition.SetLine(targetPosition.GetLine() + 1);
		break;
	case 4:
		targetPosition.SetColumn(targetPosition.GetColumn());
		targetPosition.SetLine(targetPosition.GetLine() - 1);
		break;
	}

	targetPosition.SetColumn(Maximum(targetPosition.GetColumn(), 'a'));
	targetPosition.SetLine(Maximum(targetPosition.GetLine(), 'A'));
	targetPosition.SetColumn(Minimum(targetPosition.GetColumn(), maxColumns + 'a' - 1));
	targetPosition.SetLine(Minimum(targetPosition.GetLine(), maxLines + 'A' - 1));
	
	target = targetPosition;
}

//==========================================================================================//
//Get Target Position
//Returns the bomb target as PositionChar.

Position<char> Bomb::GetTargetPosition()
{
	Position<char> target;
	target.SetLine(this->target.GetLine());
	target.SetColumn(this->target.GetColumn());
	return target;
}
