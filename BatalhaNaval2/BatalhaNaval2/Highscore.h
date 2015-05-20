#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include "Score.h"

#include <vector>
#include <string>

using namespace std;

class Highscore
{
public:
	Highscore();
	void InsertScore(const Score &score);
	void InsertScore(string name, time_t score);
	void ShowHighscore() const;
	void AddScore(string name, time_t score);
	~Highscore();
private:
	bool hasChanged;
	vector<Score> scores;
};

#endif