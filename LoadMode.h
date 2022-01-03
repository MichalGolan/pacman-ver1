#ifndef _LOADMOAD_H
	#define _LOADMOAD_H

#include "Game.h"

class LoadMode : public Game
{
public:
	void		 	  setMapForLoad();
	virtual void	  runScreen(int&);
	virtual void      prepareToRun(int& runGame);
	Position::compass getStep(stringstream& file);
	Position		  extractPos(const string&);

private:
	vector<string> _stepsFiles;
};



#endif