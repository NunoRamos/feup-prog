#ifndef BOMB_H
#define BOMB_H

#include "Position.h"

class Bomb
{
public:
	Bomb(PositionChar targetPosition);
	PositionChar getTargetPosition() const;
	// OTHER METHODS, if necessary
	// ...
	void show() const; // shows the attributes of the bomb (for debugging)
private:
	char targetLine, targetColumn;
};
#endif