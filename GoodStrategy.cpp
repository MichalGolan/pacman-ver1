#include "GoodStrategy.h"

GoodStrategy::GoodStrategy(Map* pMap) : Strategy(pMap), _dumbTimer(0)
{
	_smartTimer = randinRange(20, 10);
	_smart = 1;
}

Position::compass GoodStrategy::go(const Position& currGPos, const Position& PacmanPos, const Position::compass& dir)
{
	Position::compass newDir;

	if (_smartTimer == 0 && _smart) // ghost go dummmy :(
	{
		//switch to dumb
		_dumbTimer = randinRange(15, 10);
		_smart = 0;
	}
	else if (_dumbTimer == 0 && !_smart) // lets get smart!
	{
		//switch to smart
		_smartTimer = randinRange(20, 15);
		_smart = 1;
	}

	if (_smart) //currently smart
	{
		newDir = goSmart(currGPos, PacmanPos);
		_smartTimer--;
	}
	else if (!_smart) //currently dumb
	{
		newDir = goDumb(currGPos, dir);
		_dumbTimer--;
	}
	return newDir;
}
