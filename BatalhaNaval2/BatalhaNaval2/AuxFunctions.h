#ifndef AUXFUNCTIONS_H
#define AUXFUNCTIONS_H

#include "Position.h"

PositionInt ConvertToPositionInt(PositionChar position);

PositionChar ConvertToPositionChar(PositionInt position);

void WaitForEnter();

void ClearScreen(); //cenas

void SetColor(unsigned int color);

void SetColor(unsigned int color, unsigned int background_color);

#endif