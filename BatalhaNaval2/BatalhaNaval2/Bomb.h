#ifndef BOMB_H
#define BOMB_H

#include "Position.h"

class Bomb
{
public:
	Bomb(PositionChar targetPosition);
	PositionChar GetTargetPosition() const;
private:
	char targetLine, targetColumn;
};
#endif