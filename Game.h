#ifndef _GAME_H
	#define _GAME_H

#include <iostream>
#include "Map.h"
#include "Pacman.h"
#include "Ghost.h"

using namespace std;

class Game {

private:
	Map _map;
	Pacman _pacman;
	Ghost _ghosts[2];
	int _breadcrumbs;
	int _lives;
	int _colourfulGame;

	void printInfo();

public:
	Game();
	~Game();
	void initGhosts();
	void set(int& play);
	void run();
	int validMove(char key);
	void handleNextMove();
	Position getNextPos();
	Position getNextNextPos();
	int pacmanGhostMeet();

	void printMenu() const;
	void pause();
};

#endif
