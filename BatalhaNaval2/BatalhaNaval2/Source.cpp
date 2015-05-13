#include <stdlib.h> 
#include <time.h>
#include <iostream>
#include <string>
#include <fstream>

#include "Player.h"
#include "AuxFunctions.h"

using namespace std;

int main()
{
	srand((unsigned int) time(NULL));
	string playerName;
	string boardFileName;
	unsigned int turn = rand()%2;
	time_t timer;
		

	cout << "Qual e o nome do jogador 1?\nNome: ";
	cin >> playerName;
	cout << "Qual o nome do ficheiro de tabuleiro?\nNome: ";
	cin >> boardFileName;
	Player player1 = Player(playerName, boardFileName);

	cout << endl;
	player1.showBoard();
	WaitForEnter();
	ClearScreen();

	cout << "Qual e o nome do jogador 2?\nNome: ";
	cin >> playerName;
	cout << "Qual o nome do ficheiro de tabuleiro?\nNome: ";
	cin >> boardFileName;
	Player player2 = Player(playerName, boardFileName);

	cout << endl;
	player2.showBoard();
	WaitForEnter();
	ClearScreen();

	while (!player1.FleetDestroyed() && !player2.FleetDestroyed())
	{
		string targetString;
		if (turn % 2 == 0) // JOGADOR 1
		{
			cout << "JOGADOR 1 - " << player1.GetName() <<"\n\n";
			player2.showBoard();
			cout << player2.GetName() << ", para onde quer enviar a bomba?\n";
			timer = time(NULL);
			cin >> targetString;
			timer = time(NULL); -timer;
			player1.AddTimeElapsed(timer);
			player2.attackBoard(player1.getBomb(targetString));
			player2.showBoard();
		}
		else  //JOGADOR 2
		{
			cout << "JOGADOR 2 - " << player2.GetName() <<"\n\n";
			player1.showBoard();
			cout << player2.GetName() << ", para onde quer enviar a bomba?\n";
			timer = time(NULL);
			cin >> targetString;
			timer = time(NULL) - timer;
			player1.AddTimeElapsed(timer);
			player1.attackBoard(player2.getBomb(targetString));
			player1.showBoard();
		} 
		turn++;
		WaitForEnter();
		ClearScreen();
	}

	if (player1.FleetDestroyed())
		cout << "Parabéns. O jogador 2 venceu!\n";
	else
		cout << "Parabéns. O jogador 1 venceu!\n";


	return 0;
}