#ifndef _GAME_H
	#define _GAME_H

#include <iostream>
#include "Map.h"
#include "Pacman.h"
#include "Ghost.h"

using namespace std;

const int LOSE = 0;
const int GO = 1;
const int WIN = 2;
const int MENU = 4;
const int DATALINE = 5;

class Game {

public:
	//c'tors
	Game();

	//setters
	void initGhosts();

	//gameplay methods
	void set(int& play);
	void run();
	int validMove(char& key);
	int isNextLocationWall(Position::compass dir, Position nextLocation) const;
	void handlePacmanMove();
	int notAPath() const;
	void handleGhostMove();
	int pacmanGhostMeet();
	void pause(int& play);
	void endGame(int& play);

	//printing methods
	void printByIndex(int index) const;	

private: //data members
	Map    _map;
	Pacman _pacman;
	Ghost  _ghosts[2];
	int    _breadcrumbs;
	int    _lives;
	int    _colourfulGame;
};

#endif
