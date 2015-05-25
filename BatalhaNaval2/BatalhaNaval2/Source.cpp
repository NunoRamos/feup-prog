#include <stdlib.h> 
#include <time.h>
#include <iostream>
#include <string>
#include <fstream>

#include "Player.h"
#include "AuxFunctions.h"
#include "Highscore.h"

using namespace std;

//==========================================================================================//
//Menu
//Shows the menu and lets the user select an option.
//Returns the option's number. 

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

bool DoesFileExist(string filename)
{
	ifstream file;

	file.open(filename);
	if (file.fail())
	{
		cout << "File does not exist.\n";
		return false;
	}
	return true;
}


//==========================================================================================//
//Board Setup
//Ask the user(s) the players' name and the board files name.
//Returns nothing.

void BoardSetup(Player &player1, Player &player2)
{
	string playerName;
	string boardFileName;

	cout << "What is the 1st player's name?\nName: ";
	cin.ignore(1000, '\n');
	getline(cin, playerName);
	cout << "What is the board file name? Press Ctrl+Z to quit.\nName: ";
	do
	{
		cin >> boardFileName;
		if (cin.eof())
			exit(1);
		if (boardFileName.find(".txt") == -1)
			boardFileName = boardFileName + ".txt";
	} while (!DoesFileExist(boardFileName));
	player1 = Player(playerName, boardFileName);

	cout << endl;
	cout << player1;
	WaitForUserInput();
	ClearScreen();

	cout << "What is the 2nd player's name?\nName: ";
	getline(cin, playerName);
	cout << "What is the board file name?\nName: ";
	do
	{
		cin >> boardFileName;
		if (cin.eof())
			exit(1);
		if (boardFileName.find(".txt") == -1)
			boardFileName = boardFileName + ".txt";
	} while (!DoesFileExist(boardFileName));
	player2 = Player(playerName, boardFileName);

	cout << endl;
	cout << player2;
	WaitForUserInput();
	ClearScreen();

}

//==========================================================================================//
//Play
//Takes care of the general aspect of the game: whose turn it is, if a player has won, etc.
//Returns nothing.

void Play(Player &player1, Player &player2, Highscore &highscore)
{
	srand((unsigned int)time(NULL));
	unsigned int turn = rand() % 2 + 2;
	time_t timer;

	while (!player1.IsFleetDestroyed() && !player2.IsFleetDestroyed())
	{
		string targetString;
		if (turn % 2 == 0) // JOGADOR 1
		{
			cout << "PLAYER 1 - " << player1.GetName() << " - TURN " << turn / 2 << "\n\n";
			cout << player2;
			cout << player1.GetName() << ", where do you want to send the bomb?\n";
			timer = time(NULL);
			cin >> targetString;
			timer = time(NULL) - timer;
			player1.AddTimeElapsed(timer);
			player2.AttackBoard(player1.GetBomb(targetString));
			cout << player2;
		}
		else  //JOGADOR 2
		{
			cout << "PLAYER 2 - " << player2.GetName() << " - TURN " << turn / 2 << "\n\n";
			cout << player1;
			cout << player2.GetName() << ", where do you want to send the bomb?\n";
			timer = time(NULL);
			cin >> targetString;
			timer = time(NULL) - timer;
			player2.AddTimeElapsed(timer);
			player1.AttackBoard(player2.GetBomb(targetString));
			cout << player1;
		}
		turn++;
		WaitForUserInput();
		ClearScreen();
	}

	if (player1.IsFleetDestroyed())
	{
		cout << "Congratulations! " << player2.GetName() << " has won!\n";
		highscore.InsertScore(player2.GetScore());
	}
	else
	{
		cout << "Congratulations! " << player1.GetName() << " has won!\n";
		highscore.InsertScore(player1.GetScore());
	}

	WaitForUserInput();
}

//==========================================================================================//
//Main
//Decides what to do given the option the user chose.
//Returns 0 if the program was successfuly executed. Returns 1 if there was an invalid input in the menu.

int main()
{
	Highscore highscore;

	while (true)
	{
		Player player1, player2;

		switch (Menu())
		{
		case 1:
			BoardSetup(player1, player2);
			Play(player1, player2, highscore);
			break;
		case 2:
			highscore.ShowHighscore();
			WaitForUserInput();
			break;
		case 3:
			return 0;
		default:
			return 1;
		}
	}

	return 0;
}