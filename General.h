#ifndef _GENERAL_H
	#define _GENERAL_H

#pragma warning(disable: 4996)

#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <conio.h>


#include "Colour.h"

using namespace std;

void gotoxy(int x, int y);
void setTextColour(Colour);
void lower(char& ch);

#endif