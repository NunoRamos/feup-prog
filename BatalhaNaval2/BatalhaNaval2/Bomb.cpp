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
		target.SetColumn(targetPosition.GetColumn() + 1);
		target.SetLine(targetPosition.GetLine());
		break;
	case 2:
		target.SetColumn(targetPosition.GetColumn() - 1);
		target.SetLine(targetPosition.GetLine());
		break;
	case 3:
		target.SetColumn(targetPosition.GetColumn());
		target.SetLine(targetPosition.GetLine() + 1);
		break;
	case 4:
		target.SetColumn(targetPosition.GetColumn());
		target.SetLine(targetPosition.GetLine() - 1);
		break;
	}

	target.SetColumn(Maximum(target.GetColumn(), 'a'));
	target.SetLine(Maximum(target.GetLine(), 'A'));
	target.SetColumn(Minimum(target.GetColumn(), maxColumns + 'a' -1));
	target.SetLine(Minimum(target.GetLine(), maxLines + 'A'-1));
	
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
