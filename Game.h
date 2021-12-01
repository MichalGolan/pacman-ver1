#ifndef _GAME_H
	#define _GAME_H

#include <iostream>
#include "Map.h"
#include "Pacman.h"
#include "Ghost.h"

using namespace std;

//gameplay keys consts
const int ESC = 27;
const int ENTER = 13;

//printing and gameplay method consts
const int LOSE = 0;
const int GO = 1;
const int WIN = 2;
const int MENU = 4;
const int DATALINE = 5;
const int INVALID = 6;

class Game {

public:
	//c'tor
	Game();

	//prepares to run the game
	void set(int& play);

private:
	//handle colours
	int  askForColours();
	void colourIt();

	//runs the entire game
	void run();

	//creatures movement
	int      validMove(char& key);
	int      isNextLocationWallorTunnel(Position::compass dir, Position nextLocation) const;
	void     handleTunnel(Position pos);
	Position isATunnel(Position pos) const;
	int      notAPath() const;
	void     handlePacmanMove();
	void     handleGhostMove();
	void     resetCreatures();

	int      pacmanGhostMeet();


	//gameplay
	void pause(int& play);
	void endGame(int& play);

	//printing methods
	void printByIndex(int index) const;	

	//setters
	void initGhosts();

	//getters
	int      getDirectionKey(char key) const; // mimi

private:
	void setArrowKeys(const char* keys);  // "waxd s" //mimi

private: //data members
	Map    _map;
	Pacman _pacman;
	Ghost  _ghosts[2];
	int    _breadcrumbs;
	int    _lives;
	int    _colourfulGame;
	char   _arrowKeys[5]; //mimi

};

#endif
