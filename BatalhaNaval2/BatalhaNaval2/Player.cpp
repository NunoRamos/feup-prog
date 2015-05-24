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
	if (playerName.size() != 0)
		name = playerName;
	else
		name = "Player";
	board = Board(boardFileName);
	shipsLeft = board.GetShipsLeft();
	timeElapsed = 0;
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

string Player::GetName() const
{
	return name;
}

//==========================================================================================//
//Get Score
//Returns the player's score as a struct.

Score Player::GetScore() const
{
	Score temp;

	temp.name = name;
	temp.score = timeElapsed*board.GetShipsArea()/board.GetBoardArea();

	return temp;
}

//==========================================================================================//
//Get Bomb
//Creates a bomb depending on the target provided by the user.
//Returns a bomb.

Bomb Player::GetBomb(string targetString) const
{
	Position<char> target;

	NormalizeTargetString(targetString);

	target.SetLine(targetString.at(0));
	target.SetLine(targetString.at(1));

	Bomb bomb(target, board.GetLines(), board.GetColumns());

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

void Player::AttackBoard(Bomb &b)
{
	Position<char> bombPosition = b.GetTargetPosition();

	board.MoveShips();
	//board.Update();
	int shipAttack = board.Attack(b);
	if (shipAttack == -1)
		cout << "You have missed the ship.";
	else
		if (shipAttack == -2)
		{
			cout << "You have hit a part of a ship that had already been damaged.";
		}
	else
	{
		Ship attackedShip = board.GetShip(shipAttack);
		Position<char> position = ConvertToPositionChar(attackedShip.GetShipPosition());
		if (attackedShip.GetShipOrientation() == 'V')
			position.SetLine(position.GetLine() + attackedShip.GetLastPartDestroyed());
		else
			position.SetColumn(position.GetColumn() + attackedShip.GetLastPartDestroyed());

		cout << "You have hit ";
		SetColor(attackedShip.GetShipColor());
		cout << attackedShip.GetShipSymbol();
		SetColor(15);
		cout << ".";

		if (attackedShip.IsDestroyed())
			cout << "\nYou have sunk the ship.";
	}

	cout << "\nThe bomb fell at " << bombPosition.GetLine() << bombPosition.GetColumn() << ".\n\n";

	shipsLeft = board.GetShipsLeft();
}

