#ifndef _GAME_H
	#define _GAME_H

#include <iostream>
#include "Map.h"
#include "Pacman.h"
#include "Ghost.h"

using namespace std;

class Game {

public:
	//c'tors
	Game();

	//setters
	void initGhosts();

	//gameplay methods
	void set(int& play);
	void run();
	int validMove(char key);
	void handleNextMove();
	Position getNextPos();
	Position getNextNextPos();
	int pacmanGhostMeet();
	char pause();
	void printPause();

	//printing methods
	void printInfo();
	void printMenu() const;
	

private: //data members
	Map    _map;
	Pacman _pacman;
	Ghost  _ghosts[2];
	int    _breadcrumbs;
	int    _lives;
	int    _colourfulGame;
};

#endif
