#ifndef _GAME_H
	#define _GAME_H

#include "Pacman.h"
#include "Ghost.h"
#include "Fruit.h"

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

class Game {

public:
	//c'tor
	Game();
	~Game();
	//prepares to run the game
	void set(int& runGame);

private:
	void prepareToRun(int& runGame);

	//difficulty
	int askForDifficulty();

	//handle colours
	int  askForColours() const;
	void colourIt();

	//files
	void getFiles(vector<string>& screenFiles);
	int askForFile(const vector<string>& fileNames) const;
	int  findInVector(const string& fname) const;

	//runs the entire game
	void runScreen(int&);
	void run();

	//creatures
	void	 updateCreaturesByMap();
	int      validMove(char& key); 
	void     resetCreatures();

	void	 meetings();
	void     pacmanGhostMeet(); 


	//gameplay
	void pause(int& play);
	void endGame(int& play);

	//printing methods
	void printByIndex(int index) const;	

	//setters
	void initGhosts();
	void setMap(int&);

	//getters
	int      getDirectionKey(char key) const;

private:
	void setArrowKeys(const char* keys);  // "waxd s"

private: //data members
	Map*			 _map;
	Pacman			 _pacman;
	vector<Ghost>	 _ghosts;
	vector<string>   _files;
	Fruit			 _fruit;
	int				 _lives, _colourfulGame, _difficulty;
	char			 _arrowKeys[5];

};

#endif
