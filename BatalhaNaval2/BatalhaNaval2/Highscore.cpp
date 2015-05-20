#include "Highscore.h"

#include <fstream>

const unsigned int NAME_SIZE = 10;
const unsigned int TIME_SIZE = 10;
const unsigned int HIGHSCORE_SIZE = 10;

Highscore::Highscore()
{
	fstream file;
	string name;
	time_t score;
	char[] 
		
	file.open("highscore.dat", ios::binary);

	while (!file.eof())
	{
		file.readsome(name, NAME_SIZE);
		file.readsome(score, TIME_SIZE);
		//ok percebi
	}
}