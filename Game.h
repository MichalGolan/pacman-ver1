#ifndef _GAME_H
	#define _GAME_H

using namespace std;

#include <iostream>
#include "Map.h"
#include "Pacman.h"
#include "Ghost.h"
#include "Fruit.h"
#include <vector>


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
	int      validMove(char& key); //Game
	void     resetCreatures();// --------------------------------------------> seperate to pacman restart and ghost restart 
//-------------------------------------------------------------------------> and a virtual reset in creature

	void	 meetings();
	void     pacmanGhostMeet(); //Game


	//gameplay
	void pause(int& play);
	void endGame(int& play);

	//printing methods
	void printByIndex(int index) const;	

	//setters
	void initGhosts();

	//getters
	int      getDirectionKey(char key) const;

private:
	void setArrowKeys(const char* keys);  // "waxd s"

private: //data members
	Map				 _map;
	Pacman			 _pacman;
	vector<Ghost>	 _ghosts;
	Fruit			 _fruit;
	int				 _lives;
	int				 _colourfulGame;
	char			 _arrowKeys[5];

};

#endif
//if(_pacman.pacmnfruitmeet(_fruit_locatin))
{
	fruit.setcounter(0);
}