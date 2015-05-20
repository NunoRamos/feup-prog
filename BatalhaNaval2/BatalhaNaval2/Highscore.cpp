#include "Highscore.h"

#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

const string HIGHSCORE_FILENAME = "highscore.bin";
const unsigned int NAME_SIZE = 10;
const unsigned int TIME_SIZE = 10;
const unsigned int HIGHSCORE_SIZE = 10;


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
		file.seekg(ios::beg);
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
	}
	}

	file.close();
}

Score Highscore::operator[] (unsigned int index) const
{
	return scores.at(index);
}

bool Highscore::InsertScore(const Score &score)
{
	int i = 0;

	if (scores.size() == 0)
	{
		scores.push_back(score);
		return true;
	}

	for (i = 0; i < scores.size(); i++)
	{
		if (score.score < scores.at(i).score)
		{
			scores.insert(scores.begin() + i, score);
			if (scores.size() > 10)
				scores.pop_back();
			if (i == 9)
				return false;
			else
				return true;
		}
	}
}

void Highscore::ShowHighscore()
{
	cout << "|=========================================|\n"
		<< "|                HIGHSCORES               |\n"
		<< "|=========================================|\n";
	if (scores.size() == 0)
	{ 
		cout << "|     NAO HA HIGHSCORES DISPONIVEIS       |\n";
	}
	else
	{
		cout <<  "| No.         Name         Score          |\n";
	for (size_t i = 0; i < scores.size(); i++)
	{
		cout << "| " << setw(2) << i + 1 << ' ' << setw(10)
			<< scores.at(i).name << setw(NAME_SIZE) << setw(10) << ' '
			<< setw(TIME_SIZE) <<scores.at(i).score << "|\n";
	}
	}
	cout << "|=========================================|\n";
		
}

void Highscore::AddScore(string name, time_t score)
{
	Score temp;

	temp.name = name;
	temp.score = score;

	InsertScore(temp);
}

Highscore::~Highscore()
{
	ofstream file;
	char buffer[TIME_SIZE];

	file.open(HIGHSCORE_FILENAME, ios::trunc || ios::binary );

	int size = file.end - file.beg;

	//falta corrigir esta merda toda

	for (size_t i = 0; i < scores.size(); i++)
	{
		file.write(scores.at(i).name.c_str(), NAME_SIZE);
		itoa(scores.at(i).score, buffer, 10);
		file.write(buffer, TIME_SIZE);
	}

	file.close();
}