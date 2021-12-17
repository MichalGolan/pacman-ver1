#ifndef _SMARTSTRATEGY_H
	#define _SMARTSTRATEGY_H

#include "Strategy.h"

class SmartStrategy : public Strategy
{
public:
	SmartStrategy(Map* pMap = nullptr) : Strategy(pMap) {}
	Position::compass go(const Position& currGPos, const Position& PacmanPos, const Position::compass& dir);
};
#endif