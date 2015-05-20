#ifndef BOARD_H
#define BOARD_H

#include "Ship.h"
#include "Bomb.h"

#include<vector>
#include<string>


using namespace std;

class Board
{
public:
	Board();
	Board(const string &filename); // loads board from file 'filename'
	Ship GetShip(unsigned int shipIndex);

	void MoveShips(); // tries to randmonly move all the ships of the fleet
	bool MoveShip(unsigned int shipIndex);
	bool CanPlaceShip(const Ship &s);
	
	void Update();
	bool PutShip(const Ship &s, int shipIndex); // adds ship to the board, if possible; Adicionei shipIndex por ser conveniente
	void RemoveShip(const Ship &s);
	
	int Attack(const Bomb &b);
	
	unsigned int GetShipsLeft();
	
	void Display() const; // displays the colored board during the game

private:
	int numLines, numColumns; // redundant info …
	vector<Ship> ships; // ships that are placed on the board
	vector<vector<int>> board; // each element indicates
	// the index of a ship in the 'ships' vector
	// (in the range 0..ships.size()-1) ;
	// -1 is used to represent the sea
};
#endif