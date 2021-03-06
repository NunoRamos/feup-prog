﻿#ifndef PLAYER_H
#define PLAYER_H

#include "Bomb.h"
#include "Board.h"
#include "Score.h"

#include<string>

using namespace std;

class Player
{
public:
	Player();
	Player(string playerName, string boardFileName);
	Bomb GetBomb(string targetString) const; // asks bomb target coordinates and creates the bomb
	bool IsFleetDestroyed() const; // checks if player's fleet is destroyed
	string GetName() const;
	Score GetScore() const;
	time_t GetTimeElapsed() const;
	Board GetBoard() const;
	friend ostream& operator<<(ostream& out, Player&);
	void AddTimeElapsed(time_t time);
	void AttackBoard(Bomb &b); // "receives" a bomb from the opponent;
	// updates own board taking into account the damages
	// caused by the bomb; BEFORE THAT moves the ships
private:
	string name; // name of the player
	Board board; // boaard of the player
	time_t timeElapsed;
	unsigned int shipsLeft;
};
#endif