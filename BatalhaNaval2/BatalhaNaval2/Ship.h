#ifndef SHIP_H
#define SHIP_H


#include <string>
#include <vector>

#include"Position.h"

using namespace std;

class Ship
{
public:
	Ship(char symbol, Position<char> position, char orientation, unsigned int size,
	unsigned int color);
	unsigned int GetShipSize() const;
	Position<unsigned int> GetShipPosition() const;
	int GetLastPartDestroyed() const;
	int GetShipColor() const;
	void SetShipPosition(Position<unsigned int> position);
	void SetShipOrientation(char orientation);
	char GetShipOrientation() const;
	char GetShipStatusSymbol(Position<unsigned int> position);
	string GetShipStatus() const;
	char GetShipSymbol() const;
	bool MoveRand(unsigned int lineMin, unsigned int columnMin, unsigned int lineMax, unsigned int columnMax); // moves the ship randomly
	bool Attack(size_t partNumber); //partNumber = {0,1,…, size-1}
	bool IsDestroyed() const; // checks whether the ship is destroyed
private:
	int lastPartDestroyed;
	char symbol; // 'P' = "porta-aviões"; 'F' = "fragata"; … (portuguese names)
	Position<unsigned int> position; // coordinates of the upper left corner of the ship
	char orientation; // 'H' = horizontal; 'V' = vertical
	unsigned int size; // number os cells occupied by the ship, on the board
	unsigned int color; // color code: o=BLACK, 1=BLUE, … (see annex of 1st proj.)
	string status; // status[i]: uppercase = good; lowercase = damaged
	// ex: "FFFF" means that the "fragata" is intact;
	// ex: "FFfF" means that the 'partNumber' 2 was hit by a bomb
	// OTHER ATTRIBUTES OR METHODS, if necessary
	// ...
};
#endif
