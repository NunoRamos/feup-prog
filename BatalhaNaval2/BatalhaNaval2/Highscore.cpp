#include "Highscore.h"

#include <fstream>

const string HIGHSCORE_FILENAME = "highscore.dat";
const unsigned int NAME_SIZE = 10;
const unsigned int TIME_SIZE = 10;
const unsigned int HIGHSCORE_SIZE = 10;


Highscore::Highscore()
{
	ifstream file;
	char name[NAME_SIZE], score[HIGHSCORE_SIZE];
	Score temp;
	
		
	file.open(HIGHSCORE_FILENAME, ios::binary);
	

	while (!file.eof())
	{
		file.readsome(name, NAME_SIZE);
		file.readsome(score, TIME_SIZE);
		temp.name = name;
		temp.score = stoi(score);
		scores.push_back(temp);
	}

	file.close();
}

Score Highscore::operator[] (unsigned int index) const
{
	return scores.at(index);
}

bool Highscore::InsertScore(const Score &score)
{
	for (size_t i = 0; i < scores.size(); i++)
	{
		if (score.score < scores.at(i).score)
		{
			scores.insert(scores.begin() + i, score);
		}
	}

	if (scores.size() > 10)
		scores.pop_back;

	return true;
}

Highscore::~Highscore()
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