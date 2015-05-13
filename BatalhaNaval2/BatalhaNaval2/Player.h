#ifndef PLAYER_H
#define PLAYER_H

#include "Bomb.h"
#include "Board.h"

#include<string>

using namespace std;

class Player
{
public:
	Player();
	Player(string playerName, string boardFileName);
	void showBoard() const; // shows the player’s board
	Bomb getBomb(string targetString) const; // asks bomb target coordinates and creates the bomb
	bool FleetDestroyed() const; // checks if player's is destroyed
	string GetName();
	time_t GetTimeElapsed() const;
	time_t AddTimeElapsed(time_t time);
	void attackBoard(const Bomb &b); // "receives" a bomb from the opponent;
	// updates own board taking into account the damages
	// caused by the bomb; BEFORE THAT… moves the ships
private:
	string name; // name of the player
	Board board; // board of the player
	time_t timeElapsed;
	unsigned int shipsLeft;
};
#endif