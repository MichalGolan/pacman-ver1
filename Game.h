#ifndef _GAME_H
	#define _GAME_H

#include "Pacman.h"
#include "Ghost.h"
#include "Fruit.h"


class Game {

public:
	//c'tor
	Game();
	~Game();
	//prepares to run the game
	void set(int& runGame);
	virtual void prepareToRun(int& runGame);
	void run();

protected:
	//difficulty
	int askForDifficulty();

	//handle colours
	int  askForColours() const;
	void colourIt();

	//files
	void getFiles(vector<string>& screenFiles);
	int askForFile(const vector<string>& fileNames) const;

	//runs the entire game
	virtual void runScreen(int&);

	//creatures
	void	 updateCreaturesByMap();
	int      validMove(char& key); 
	void     resetCreatures();

	int	 meetings();
	int     pacmanGhostMeet(); 


	//gameplay
	void pause(int& play);
	virtual void endGame(int& play);

	//printing methods
	void printByIndex(int index) const;	

	//setters
	void initGhosts();
	void setMap(int&);

	//getters
	int      getDirectionKey(char key) const;

protected:
	void setArrowKeys(const char* keys);  // "waxd s"

protected: //data members
	Map*			 _map;
	Pacman			 _pacman;
	vector<Ghost>	 _ghosts;
	vector<string>   _files;
	Fruit			 _fruit;
	int				 _lives, _colourfulGame, _difficulty;
	char			 _arrowKeys[5];

};

#endif
