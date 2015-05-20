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

void Play()
{
	srand((unsigned int)time(NULL));
	string playerName;
	string boardFileName;
	unsigned int turn = rand() % 2;
	time_t timer;

	cout << "Qual e o nome do jogador 1?\nNome: ";
	cin >> playerName;
	cout << "Qual o nome do ficheiro de tabuleiro?\nNome: ";
	cin >> boardFileName;
	Player player1 = Player(playerName, boardFileName);

	cout << endl;
	player1.ShowBoard();
	WaitForEnter();
	ClearScreen();

	cout << "Qual e o nome do jogador 2?\nNome: ";
	cin >> playerName;
	cout << "Qual o nome do ficheiro de tabuleiro?\nNome: ";
	cin >> boardFileName;
	Player player2 = Player(playerName, boardFileName);

	cout << endl;
	player2.ShowBoard();
	WaitForEnter();
	ClearScreen();

	while (!player1.FleetDestroyed() && !player2.FleetDestroyed())
	{
		string targetString;
		if (turn % 2 == 0) // JOGADOR 1
		{
			cout << "JOGADOR 1 - " << player1.GetName() << "\n\n";
			player2.ShowBoard();
			cout << player2.GetName() << ", para onde quer enviar a bomba?\n";
			timer = time(NULL);
			cin >> targetString;
			timer = time(NULL) - timer;
			player1.AddTimeElapsed(timer);
			player2.AttackBoard(player1.GetBomb(targetString));
			player2.ShowBoard();
		}
		else  //JOGADOR 2
		{
			cout << "JOGADOR 2 - " << player2.GetName() << "\n\n";
			player1.ShowBoard();
			cout << player2.GetName() << ", para onde quer enviar a bomba?\n";
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

	if (player1.FleetDestroyed())
		cout << "Parabens. O jogador 2 venceu!\n";
	else
		cout << "Parabens. O jogador 1 venceu!\n";
}

int main()
{
	Highscore highscore;

	while (true)
	{
		switch (Menu())
		{
		case 1:
			Play();
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