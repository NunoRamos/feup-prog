#include "Player.h"
#include "AuxFunctions.h"

#include <string>
#include<iostream>

//==========================================================================================//
//Player Default Constructor

Player::Player()
{

}

//==========================================================================================//
//Player Constructor
//Sets the player's name according to the first argument.
//Assigns him/her a board depending on the board file provided.

Player::Player(string playerName, string boardFileName)
{
	name = playerName;
	board = Board(boardFileName);
	shipsLeft = board.GetShipsLeft();
	timeElapsed = 0;
}

//==========================================================================================//
//Show Board
//Displays board.

void Player::ShowBoard() const
{
	board.Display();
}

//==========================================================================================//
//Is Fleet Destroyed
//Checks if the player's fleet is destroyed.
//Returns true if there are no ships left. Returns false otherwise.

bool Player::IsFleetDestroyed() const
{
	if (shipsLeft == 0)
		return true;
	else
		return false;
}

//==========================================================================================//
//Get Name
//Returns the player's name.

string Player::GetName()
{
	return name;
}

//==========================================================================================//
//Get Bomb
//Creates a bomb depending on the target provided by the user.
//Returns a bomb.

Bomb Player::GetBomb(string targetString) const
{
	PositionChar target;

	target.lin = targetString.at(0);
	target.col = targetString.at(1);

	Bomb bomb(target);

	return bomb;
}

//==========================================================================================//
//Get Time Elapsed
//Returns the sum of time elapsed during all the player's turn

time_t Player::GetTimeElapsed() const
{
	return timeElapsed;
}

//==========================================================================================//
//Add Time Elapsed
//Adds time elapsed.

void Player::AddTimeElapsed(time_t time)
{
	timeElapsed += time;
}

//==========================================================================================//
//Attack Board
//Makes the ships move and then tries to attack them. 

void Player::AttackBoard(const Bomb &b)
{
	board.MoveShips();
	board.Update();
	int shipAttack = board.Attack(b);
	if (shipAttack == -1)
		cout << "You have missed the ship.\n\n";
	else
	{
		Ship attackedShip = board.GetShip(shipAttack);
		PositionChar position = ConvertToPositionChar(attackedShip.GetShipPosition());
		if (attackedShip.GetShipOrientation() == 'V')
			position.lin += attackedShip.GetLastPartDestroyed();
		else
			position.col += attackedShip.GetLastPartDestroyed();

		cout << "You have hit " << attackedShip.GetShipSymbol() << " at " << position.lin << position.col << ".\n\n";
	}

	shipsLeft = board.GetShipsLeft();
}