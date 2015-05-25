#include "Highscore.h"

#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

const string HIGHSCORE_FILENAME = "highscore.txt";
const unsigned int NAME_SIZE = 10;
const unsigned int TIME_SIZE = 10;
const unsigned int HIGHSCORE_SIZE = 10;

//========================================================================================= //
//Highscore Default Constructor
//Reads the highscore binary file and fills the "scores" vector.

Highscore::Highscore()
{
	ifstream file;
	Score temp;
	int i = 0;

	file.open(HIGHSCORE_FILENAME);

	if (file.is_open())
	{
		string buffer;
		file.peek();
		while (!file.eof() && i < 10)
		{
			getline(file, temp.name, '-');
			getline(file, buffer, ';');
			temp.score = stod(buffer);
			file.ignore(1000, '\n');
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

	hasChanged = true; //remove


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
				break;
			}
		}
		if (i == scores.size())
			scores.push_back(score);
		if (scores.size() > 10)
			scores.pop_back();
		if (i != 9)
			hasChanged = true;
	}
}

void Highscore::InsertScore(string name, double score)
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
			cout << "| " << setw(2) << i + 1 << ' ' << setw(13)
				<< scores.at(i).name << setw(NAME_SIZE) << setw(5) << ' '
				<< setw(TIME_SIZE) << scores.at(i).score << setw(11) << "|\n";
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
		ostringstream ss;
		ofstream file;
		file.open(HIGHSCORE_FILENAME);

		for (size_t i = 0; i < scores.size(); i++)
		{
			ss << scores.at(i).name << '-' << scores.at(i).score << ';' << endl;
		}

		file << ss.str();
		file.close();
	}
}