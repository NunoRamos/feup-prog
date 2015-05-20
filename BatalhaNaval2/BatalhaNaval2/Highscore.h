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
	Score operator[] (unsigned int index) const;
	bool Highscore::InsertScore(const Score &score);

private:
	vector<Score> scores;
};

#endif