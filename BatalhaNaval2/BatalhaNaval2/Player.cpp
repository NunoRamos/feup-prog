#include "Player.h"
#include "AuxFunctions.h"

#include <string>
#include<iostream>

Player::Player()
{
	name = "Player";
	board = Board("board.txt");
	shipsLeft = board.ShipsLeft();
	timeElapsed = 0;
}

Player::Player(string playerName, string boardFileName)
{
	name = playerName;
	board = Board(boardFileName);
	shipsLeft = board.ShipsLeft();
	timeElapsed = 0;
}

void Player::ShowBoard() const
{
	board.Display();
}

bool Player::FleetDestroyed() const
{
	if (shipsLeft == 0)
		return true;
	else
		return false;
}

string Player::GetName()
{
	return name;
}

Bomb Player::GetBomb(string targetString) const
{
	PositionChar target;

	target.lin = targetString.at(0);
	target.col = targetString.at(1);

	Bomb bomb(target);

	return bomb;
}

time_t Player::GetTimeElapsed() const
{
	return timeElapsed;
}

void Player::AddTimeElapsed(time_t time)
{
	timeElapsed += time;
}

void Player::AttackBoard(const Bomb &b)
{
	board.MoveShips();
	board.Update();
	//board.display();
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

	shipsLeft = board.ShipsLeft();
}