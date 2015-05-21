#ifndef BOMB_H
#define BOMB_H

#include "Position.h"

class Bomb
{
public:
	Bomb(PositionChar targetPosition, unsigned int maxLines, unsigned int maxColumns);
	PositionChar GetTargetPosition() const;

private:
	char targetLine, targetColumn;
};
#endif