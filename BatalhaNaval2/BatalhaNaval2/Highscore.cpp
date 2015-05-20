#include "Highscore.h"

#include <fstream>

const unsigned int NAME_SIZE = 10;
const unsigned int TIME_SIZE = 10;
const unsigned int HIGHSCORE_SIZE = 10;

Highscore::Highscore()
{
	fstream file;
	char name[NAME_SIZE], score[HIGHSCORE_SIZE];
	Score temp;
	
		
	file.open("highscore.dat", ios::binary);
	

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

Score Highscore::operator[] (unsigned int index)
{
	return scores.at(index);
}

bool Highscore::InsertScore(Score score)
{
	for (size_t i = 0; i < scores.size(); i++)
	{
		if (score.score < scores.at(i).score)
		{

		}
	}

	return true;
}