#include <stdlib.h> 
#include <time.h>
#include <iostream>
#include <string>
#include <fstream>

#include "Player.h"
#include "AuxFunctions.h"
#include "Highscore.h"

using namespace std;

int Menu()
{
	int option;
	ClearScreen();
	cout << "|=========================================|\n"
		<< "|                BATTLESHIP               |\n"
		<< "|=========================================|\n"
		<< "| Select an option:                       |\n"
		<< "|                                         |\n"
		<< "|            1. Play                      |\n"
		<< "|            2. Highscores                |\n"
		<< "|            3. Exit                      |\n"
		<< "|=========================================|\n"
		<< " Select an option:  ";
	cin >> option;
	ClearScreen();

	return option;
}

void BoardSetup(Player &player1, Player &player2)
{
	string playerName;
	string boardFileName;

	cout << "What is the 1st player's name?\nName: ";
	cin >> playerName;
	cout << "What is the board file name?\nName: ";
	cin >> boardFileName;
	player1 = Player(playerName, boardFileName);

	cout << endl;
	player1.ShowBoard();
	WaitForEnter();
	ClearScreen();

	cout << "What is the 2nd player's name?\nName: ";
	cin >> playerName;
	cout << "What is the board file name?\nName: ";
	cin >> boardFileName;
	player2 = Player(playerName, boardFileName);

	cout << endl;
	player2.ShowBoard();
	WaitForEnter();
	ClearScreen();
}

void Play(Player &player1, Player &player2)
{
	srand((unsigned int)time(NULL));
	unsigned int turn = rand() % 2;
	time_t timer;


	while (!player1.IsFleetDestroyed() && !player2.IsFleetDestroyed())
	{
		string targetString;
		if (turn % 2 == 0) // JOGADOR 1
		{
			cout << "PLAYER 1 - " << player1.GetName() << "\n\n";
			player2.ShowBoard();
			cout << player2.GetName() << ", where do you want to send the bomb?\n";
			timer = time(NULL);
			cin >> targetString;
			timer = time(NULL) - timer;
			player1.AddTimeElapsed(timer);
			player2.AttackBoard(player1.GetBomb(targetString));
			player2.ShowBoard();
		}
		else  //JOGADOR 2
		{
			cout << "PLAYER 2 - " << player2.GetName() << "\n\n";
			player1.ShowBoard();
			cout << player2.GetName() << ", where do you want to send the bomb?\n";
			timer = time(NULL);
			cin >> targetString;
			timer = time(NULL) - timer;
			player1.AddTimeElapsed(timer);
			player1.AttackBoard(player2.GetBomb(targetString));
			player1.ShowBoard();
		}
		turn++;
		WaitForEnter();
		ClearScreen();
	}

	if (player1.IsFleetDestroyed())
		cout << "Congratulations. Player 2 has won!\n";
	else
		cout << "Congratulations. Player 1 has won!\n";
}

int main()
{
	Highscore highscore;
	Player player1, player2;

	while (true)
	{
		switch (Menu())
		{
		case 1:
			BoardSetup(player1, player2);
			Play(player1, player2);
			break;
		case 2:
			highscore.ShowHighscore();
			WaitForEnter();
			break;
		case 3:
			return 0;
		default:
			return 1;
		}
	}

	return 0;
}