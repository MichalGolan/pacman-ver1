#ifndef _GAME_H
	#define _GAME_H

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

#endif
