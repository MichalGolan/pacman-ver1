#ifndef _GENERAL_H
	#define _GENERAL_H

#pragma warning(disable: 4996)
//#define _HAS_STD_BYTE 0

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>
#include <vector>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "Colour.h"

using namespace std;
namespace fs = std::filesystem;

int  numOfLinesinFile(ifstream& file);
void gotoxy(int x, int y);
void setTextColour(Colour);
void lower(char& ch);
int  randinRange(int topRange, int botRange = 0);
int findInVector(const vector<string>& fileNames, const string& fname);

#endif