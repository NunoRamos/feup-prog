#ifndef AUXFUNCTIONS_H
#define AUXFUNCTIONS_H

#include "Position.h"
#include <string>

Position<unsigned int> ConvertToPositionInt(Position<char> position); //Converts PositionChar to PositionInt.

Position<char> ConvertToPositionChar(Position<unsigned int> position); //Converts PositionInt to PositionChar.

void WaitForUserInput(); //Waits for a key press from the user.

void ClearScreen(); //Clears the console screen.


void SetColor(unsigned int color); //Sets text color.

void SetColor(unsigned int color, unsigned int background_color); //Sets text and background color.

int Maximum(int n1, int n2);

int Minimum(int n1, int n2);

void NormalizeTargetString(std::string &targetString);

#endif