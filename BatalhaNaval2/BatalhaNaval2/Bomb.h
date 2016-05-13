#ifndef BOMB_H
#define BOMB_H

#include "Position.h"

class Bomb
{
public:
	Bomb(Position<char> targetPosition, unsigned int maxLines, unsigned int maxColumns);
	Position<char> GetTargetPosition();

private:
	Position<char> target;
};
#endif