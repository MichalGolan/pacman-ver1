#ifndef _SAVEMODE_H
	#define _SAVEMODE_H

#include "Game.h"

class SaveMode : public Game
{
public:
	virtual void runScreen(int&);
	void endGameAndSaveRes(int&, ofstream&);


private:
	int     _pointsInTime = 0;
	string  _currScreen;
};

#endif