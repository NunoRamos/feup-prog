#include "Highscore.h"

#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

const string HIGHSCORE_FILENAME = "highscore.dat";
const unsigned int NAME_SIZE = 10;
const unsigned int TIME_SIZE = 10;
const unsigned int HIGHSCORE_SIZE = 10;

//========================================================================================= //
//Highscore Default Constructor
//Reads the highscore binary file and fills the "scores" vector.

Highscore::Highscore()
{
	ifstream file;
	char name[NAME_SIZE], score[HIGHSCORE_SIZE];
	Score temp;
	string score_s;
	int i = 0;

	file.open(HIGHSCORE_FILENAME, ios::binary);

	if (file.is_open())
	{
		file.peek();
		while (!file.eof() && i < 10)
		{
			file.read(name, NAME_SIZE);
			file.read(score, TIME_SIZE);
			score_s = score;
			temp.name = name;
			temp.score = stoi(score_s);
			scores.push_back(temp);
			i++;
			file.peek();
		}
	}
	else
	{
		ofstream createFile;
		createFile.open(HIGHSCORE_FILENAME, ios::binary);
		createFile.close();
	}

	file.close();
	hasChanged = false;
}

//==========================================================================================//
//Insert Score
//Inserts the score provided as argument in the "scores" vector depending on its position.
//The lower the score, the lower the index. The "scores" vector has a maximum size of 10.
//So if a score is higher than scores[9], it will be discarded.

void Highscore::InsertScore(const Score &score)
{
	int i = 0;

	if (scores.size() == 0)
	{
		scores.push_back(score);
		hasChanged = true;
	}
	else
	{
		for (i = 0; i < scores.size(); i++)
		{
			if (score.score < scores.at(i).score)
			{
				scores.insert(scores.begin() + i, score);
				if (scores.size() > 10)
					scores.pop_back();
				if (i != 9)
					hasChanged = true;
			}
		}
	}
}

void Highscore::InsertScore(string name, time_t score)
{
	Score temp;
	temp.name = name;
	temp.score = score;
	InsertScore(temp);
}

//==========================================================================================//
//Show Highscore
//Shows the highscore screen. If there are no highscores set, 
//it will display a message so that the users acknowledges it.

void Highscore::ShowHighscore() const
{
	cout << "|=========================================|\n"
		<< "|                HIGHSCORES               |\n"
		<< "|=========================================|\n";
	if (scores.size() == 0)
	{
		cout << "|        NO AVAILABLE HIGHSCORES          |\n";
	}
	else
	{
		cout << "| No.         Name          Score         |\n";
		for (size_t i = 0; i < scores.size(); i++)
		{
			cout << "| " << setw(2) << i + 1 << ' ' << setw(10)
				<< scores.at(i).name << setw(NAME_SIZE) << setw(10) << ' '
				<< setw(TIME_SIZE) << scores.at(i).score << "|\n";
		}
	}
	cout << "|=========================================|\n";

}

//==========================================================================================//
//Highscore Destructor
//If the top 10 highscores have changed, the highscore file will be overwritten.
//Otherwise, it will do nothing.

Highscore::~Highscore()
{
	if (hasChanged)
	{
		ofstream file;
		char buffer[TIME_SIZE];

		file.open(HIGHSCORE_FILENAME, ios::binary);

		for (size_t i = 0; i < scores.size(); i++)
		{
			file.write(scores.at(i).name.c_str(), NAME_SIZE);
			itoa(scores.at(i).score, buffer, 10);
			file.write(buffer, TIME_SIZE);
		}

		file.close();
	}
}