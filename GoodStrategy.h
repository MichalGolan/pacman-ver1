#ifndef _GOODSTRATEGY_H
	#define _GOODSTRATEGY_H

#include "Strategy.h"

class GoodStrategy : public Strategy
{
public:
	GoodStrategy(Map* pMap = nullptr);
	Position::compass go(const Position& currGPos, const Position& PacmanPos, const Position::compass& dir);

private:
	int _smartTimer, _dumbTimer, _smart;
};

#endif