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

void Player::showBoard() const
{
	board.display();
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

Bomb Player::getBomb(string targetString) const
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

time_t Player::AddTimeElapsed(time_t time)
{
	timeElapsed += time;
}

void Player::attackBoard(const Bomb &b)
{
	board.moveShips();
	board.Update();
	//board.display();
	int shipAttack = board.attack(b);
	if (shipAttack == -1)
		cout << "Falhou o navio.\n\n";
	else
	{
		Ship attackedShip = board.GetShip(shipAttack);
		PositionChar position = ConvertToPositionChar(attackedShip.GetShipPosition());
		if (attackedShip.GetShipOrientation() == 'V')
			position.lin += attackedShip.GetLastPartDestroyed();
		else
			position.col += attackedShip.GetLastPartDestroyed();

		cout << "Acertou no navio " << attackedShip.GetShipSymbol() << " na posicao " << position.lin << position.col <<".\n\n";
	}
		
	shipsLeft = board.ShipsLeft();
}