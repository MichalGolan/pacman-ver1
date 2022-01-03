#ifndef SILENTMODE_H_
	#define SILENTMODE_H_

#include "LoadMode.h"

class SilentMode : public LoadMode
{
public:
	virtual void runScreen(int&);
	virtual void prepareToRun(int& runGame);
	void		 silentEndGame(int& play);
	void		 compareToRes();
	void		 silentRun();

private:
	vector<int>    _pointOfLose;
	int			   _victory = 0;
	int            _pointsInTime = 0;
	vector<string> _resultsFile;
	vector<string> _tests;
};

#endif