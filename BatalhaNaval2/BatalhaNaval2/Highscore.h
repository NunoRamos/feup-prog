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
		

private:
	vector<Score> scores();
};

#endif