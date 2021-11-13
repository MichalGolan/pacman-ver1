#pragma once
#include <iostream>
#include "Board.h"
using namespace std;

class Game {

private:
	Board _board;
	void printInfo();


public:
	void setGame();
	void printMenu();
	void pause();
};