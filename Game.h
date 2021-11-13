#ifndef _GAME_H
	#define _GAME_H

#include <iostream>
#include "Board.h"
#include "Pacman.h"
#include "Ghost.h"

using namespace std;

class Game {

private:
	Board _board;
	Pacman _pacman;
	Ghost _ghosts[2];
	int breadcrumbs;
	int lives;

	void printInfo();

public:
	Game();
	Game(int& play); //constructor- initializing akk datamembers
	~Game();
	void set();
	void run();
	void printMenu() const;
	void pause();
};

#endif
