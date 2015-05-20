#ifndef AUXFUNCTIONS_H
#define AUXFUNCTIONS_H

#include "Position.h"

PositionInt ConvertToPositionInt(PositionChar position); //Converts PositionChar to PositionInt.

PositionChar ConvertToPositionChar(PositionInt position); //Converts PositionInt to PositionChar.

void WaitForUserInput(); //Waits for a key press from the user.

void ClearScreen(); //Clears the console screen.

void SetColor(unsigned int color); //Sets text color.

void SetColor(unsigned int color, unsigned int background_color); //Sets text and background color.

#endif