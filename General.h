#ifndef _GENERAL_H
	#define _GENERAL_H

#pragma warning(disable: 4996)

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>
#include <vector>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <algorithm>
#include "Colour.h"

using namespace std;
namespace fs = std::filesystem;

//gameplay keys consts
const int ESC = 27;
const int ENTER = 13;

//printing and gameplay method consts
const int LOSE = 0;
const int FINISHED = 0;
const int GO = 1;
const int WIN = 2;
const int MENU = 4;
const int DATALINE = 5;
const int INVALID = 6;
const int NOFILES = 7;

int  numOfLinesinFile(ifstream& file);
void gotoxy(int x, int y);
void setTextColour(Colour);
void lower(char& ch);
int  randinRange(int topRange, int botRange = 0);
int  findInVector(const vector<string>& fileNames, const string& fname);
int  checkValidMode(int argc, char* argv[]);
string getScreenName(const string& name);

#endif